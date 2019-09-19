#include <utility>
#include <stdexcept>
#include <algorithm>
#include <functional>

#include "server.hpp"
#include "../proto/reader.hpp"
#include "../proto/consts.hpp"
#include "../proto/items.hpp"
#include "../logger.hpp"

using namespace std::placeholders; 

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
			handle_recv(*(client*)event.peer->data, cspan<unsigned char>(event.packet->data, event.packet->dataLength));
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
	logger::get().info() << cl.id() << " connected" << std::endl;

	cl.write(proto::CHANNEL_MESSAGES, proto::message::SERVER_INFO, cl.cn, proto::PROTOCOL_VERSION, 0, false, description.c_str(), "");
}

void server::handle_recv(client& cl, cspan<unsigned char> data) {
	proto::reader reader(data);
	try {
		while (!reader.ends()) {
			auto message = reader.read<proto::message>();

			switch (message) {
				case proto::message::CONNECT: {
					auto name = reader.read<std::string>();
					auto model = reader.read<proto::model>();
					auto password = reader.read<std::string>();
					auto auth_domain = reader.read<std::string>();
					auto auth_name = reader.read<std::string>();

					if (cl.info || std::get_if<player_state_spawned>(&cl.info->state) != nullptr || !password.empty() || !auth_domain.empty() || !auth_name.empty()) {
						cl.disconnect(proto::disconnect_reason::MESSAGE_ERROR);
						return;
					}

					cl.info = client_info(name, "", model, player_state_spawned());

					const auto& player_state = std::get<player_state_spawned>(cl.info->state);

					cl.write(proto::CHANNEL_MESSAGES, proto::message::MAP_CHANGE, "", proto::gamemode::COOP_EDIT, false);
					cl.write(proto::CHANNEL_MESSAGES, proto::message::SET_TEAM, cl.cn, cl.info->team.c_str(), -1);
					cl.write(proto::CHANNEL_MESSAGES, proto::message::SPAWN_STATE, cl.cn, std::bind(write_state, _1, std::cref(player_state)));
					cl.write(proto::CHANNEL_MESSAGES, std::bind(write_resume, _1, std::cref(manager)));
					
					for (const auto& c : manager) {
						if (&c == &cl || !c.info)
							continue;

						cl.write(proto::CHANNEL_MESSAGES, std::bind(write_init_client, _1, std::cref(c)));
					}

					manager.write(&cl, proto::CHANNEL_MESSAGES, std::bind(write_init_client, _1, std::cref(cl)));

					logger::get().info() << cl.id() << " joined" << std::endl;
					break;
				}

				case proto::message::POSITION: {
					static constexpr auto RAD = 3.14159265358979f / 180.0f;

					reader.read<uint32_t>();
					
					// Start of what we will send to other clients.
					auto start = reader.get_offset();

					reader.read<unsigned char>();

					auto flags = reader.read<uint32_t>();

					vector position;
					for (size_t i = 0; i < 3; i++) {
						auto a = reader.read<unsigned char>();
						auto b = reader.read<unsigned char>();
						auto value = (int32_t)a | ((int32_t)b << 8);

						if ((flags & (1 << i)) != 0) {
							auto d = reader.read<unsigned char>();

							value |= (int32_t)d << 16;
							if ((value & 0x800000) != 0) 
								value |= -16777216;
						}

						position[i] = (float)value / proto::DMF;
					}

					for (size_t i = 0; i < 3; i++) 
						reader.read<unsigned char>();

					auto magnitude = (int32_t)reader.read<unsigned char>();
					if ((flags & (1 << 3)) != 0) 
						magnitude |= ((int32_t)reader.read<unsigned char>() << 8);

					auto direction = (int32_t)reader.read<unsigned char>() | ((int32_t)reader.read<unsigned char>() << 8);
					if ((flags & (1 << 4)) != 0) {
						reader.read<unsigned char>();

						if ((flags & (1 << 5)) != 0) 
							reader.read<unsigned char>();

						if ((flags & (1 << 6)) != 0) {
							for (size_t i = 0; i < 2; i++)
								reader.read<unsigned char>();
						}
					}

					vector vel(
						(float)(direction % 360) * RAD * (float)magnitude,
						(float)(std::clamp(direction / 360, 0, 180) - 90) * RAD * (float)magnitude
					);

					if (cl.info) 
						manager.write(&cl, proto::CHANNEL_POSITIONS, proto::message::POSITION, cl.cn, reader.span_from(start, reader.get_offset()));

					break;
				}

				case proto::message::CONFIRM_SPAWN: {
					auto life_sequence = reader.read<int32_t>();
					auto weapon = reader.read<proto::weapon>();

					break;
				}

				default:
					logger::get().debug() << cl.id() << " sent an unexpected message: " << (std::underlying_type_t<proto::message>)message << std::endl;
					return;
			}
		}
	} catch (const proto::read_error& e) {
		cl.disconnect(e.is_size() ? proto::disconnect_reason::END_OF_PACKET : proto::disconnect_reason::MESSAGE_ERROR);

		logger::get().debug() << cl.id() << " read error: " << e.what() << std::endl;
	}

}

void server::handle_disconnect(client& cl) {
	if (cl.info) 
		manager.write(proto::CHANNEL_MESSAGES, proto::message::LEAVE, cl.cn);

	logger::get().info() << cl.id() << " disconnected" << std::endl;;

	manager.remove(cl);
}

void server::write_state(proto::writer& writer, const player_state_spawned& state) {
	writer.write(state.life_sequence, state.health, state.max_health, state.armor_health, state.armor, state.weapon);
	for (const auto& weapon : state.weapons) 
		writer.write(weapon.second);
}

void server::write_resume(proto::writer& writer, const client_manager& manager) {
	static const player_state_spawned DUMMY_STATE;

	writer.write(proto::message::RESUME);

	for (const auto& cl : manager) {
		if (!cl.info)
			continue;

		auto player_state = proto::player_state::ALIVE;
		auto state = std::get_if<player_state_spawned>(&cl.info->state);
		if (state == nullptr) {
			state = &DUMMY_STATE;
			player_state = std::get_if<player_state_spectator>(&cl.info->state) == nullptr ? proto::player_state::DEAD : proto::player_state::SPECTATOR;
		}

		writer.write(cl.cn, player_state, cl.info->frags, 0, state->quad_time, std::bind(write_state, _1, std::cref(*state)));
	}

	writer.write(-1);
}

void server::write_init_client(proto::writer& writer, const client& cl) {
	writer.write(proto::message::INIT_CLIENT, cl.cn, cl.info->name.c_str(), cl.info->team.c_str(), cl.info->model);
}

}