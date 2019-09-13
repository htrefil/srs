#include <utility>
#include <stdexcept>
#include <algorithm>

#include "server.hpp"
#include "../proto/reader.hpp"
#include "../proto/consts.hpp"
#include "../logger.hpp"

namespace srv {

server::server(enet_uint16 port, size_t max_clients, std::string description) : manager(max_clients), description(std::move(description)) {
	ENetAddress address;
	address.port = port;
	address.host = ENET_HOST_ANY;

	host = enet_host_create(&address, max_clients, 3, 0, 0);
	if (host == nullptr) 
		throw std::runtime_error("Failed to create host");
}

server::~server() {
	enet_host_destroy(host);
}

void server::process() {
	manager.flush();

	ENetEvent event;
	if (enet_host_service(host, &event, 1000) < 0) 
		throw std::runtime_error("Failed to check host service");

	switch (event.type) {
		case ENET_EVENT_TYPE_CONNECT: 
			handle_connect(manager.add(event.peer));
			break;
		
		case ENET_EVENT_TYPE_RECEIVE:
			handle_recv(*(client*)event.peer->data, span(event.packet->data, event.packet->dataLength));
			enet_packet_destroy(event.packet);
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			handle_disconnect(*(client*)event.peer->data);
			break;

		case ENET_EVENT_TYPE_NONE:
			break;
	}
}

void server::handle_connect(client& cl) {
	cl.write(proto::CHANNEL_MESSAGES, proto::MESSAGE_SERVER_INFO, cl.cn, proto::PROTOCOL_VERSION, 0, false, description.c_str(), "");

	logger::get().info() << cl.id() << " connected" << std::endl;
}

void server::handle_recv(client& cl, span<unsigned char> data) {
	proto::reader reader(data);

	try {
		while (!reader.ends()) {
			auto id = reader.read<int32_t>();

			switch (id) {
				case proto::MESSAGE_CONNECT: {
					auto name = reader.read<std::string>();
					auto model = reader.read<proto::model>();
					auto password = reader.read<std::string>();
					auto auth_domain = reader.read<std::string>();
					auto auth_name = reader.read<std::string>();

					if (cl.state || !password.empty() || !auth_domain.empty() || !auth_name.empty()) {
						cl.disconnect(disconnect_reason::MESSAGE);
						return;
					}

					cl.state = client_state(name, model);

					cl.write(proto::CHANNEL_MESSAGES, proto::MESSAGE_WELCOME);
					cl.write(proto::CHANNEL_MESSAGES, proto::MESSAGE_SET_TEAM, cl.cn, cl.state->team.c_str(), -1);
					cl.write(proto::CHANNEL_MESSAGES, proto::MESSAGE_SPAWN_STATE, cl.cn, write_state(*cl.state));
					
					manager.walk([&](const client& c) {
						if (&cl == &c)
							return;

						cl.write(proto::MESSAGE_INIT_CLIENT, write_init_client(c));
					});

					// TODO: resume

					logger::get().info() << cl.id() << " joined" << std::endl;
					break;
				}

				default:
					logger::get().debug() << cl.id() << " sent an invalid message ID: " << id << std::endl;

					cl.disconnect(disconnect_reason::MESSAGE);
					return;
			}	
		}		
	} catch (const proto::read_error& e) {
		logger::get().debug() << cl.id() << " read error: " << e.what() << std::endl;

		cl.disconnect(e.is_size() ? disconnect_reason::SIZE : disconnect_reason::MESSAGE);
	}

}

void server::handle_disconnect(client& cl) {
	logger::get().info() << cl.id() << " disconnected" << std::endl;;

	manager.remove(cl);
}

proto::writer::write_fn server::write_state(const client_state& state) {
	return [&](proto::writer& writer) {
		writer.write(state.life_sequence, state.health, state.max_health, state.armor_health, state.armor, state.gun);
		for (const auto& gun : state.guns) 
			writer.write(gun.second);
	};
}

proto::writer::write_fn server::write_init_client(const client& cl) {
	return [&](proto::writer& writer) {
		writer.write(cl.cn, cl.state->name.c_str(), cl.state->team.c_str(), cl.state->model);
	};
}

}