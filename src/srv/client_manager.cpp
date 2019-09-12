#include <cassert>
#include <algorithm>

#include "client_manager.hpp"

namespace srv {

client_manager::client_manager(size_t max_clients) {
	for (size_t i = 0; i < max_clients; i++)
		clients.push_back({});
}

client& client_manager::add(ENetPeer* peer) {
	for (size_t i = 0; i < clients.size(); i++) {
		if (!clients[i]) {
			clients[i] = std::move(client(peer, (int32_t)i));
			peer->data = &*clients[i];
			return *clients[i];
		}
	}

	assert(false);
}

void client_manager::remove(client& cl) {
	for (auto& p : packets) {
		if (p.exclude == &cl)
			p.exclude = nullptr;
	}

	clients[(size_t)cl.cn] = {};
}

void client_manager::flush() {
	// Broadcast.
	for (auto& p : packets) 
		broadcast(p.exclude, p.channel, p.writer.to_packet());
	
	packets.clear();

	// Clients.
	for (auto& cl : clients) {
		if (!cl)
			break;

		for (auto& p : cl->packets) 
			enet_peer_send(cl->peer, p.channel, p.writer.to_packet());
		
		cl->packets.clear();
	}
}

void client_manager::walk(std::function<void(const client&)> f) const {
	for (const auto& cl : clients) {
		if (!cl)
			continue;

		f(*cl);
	}
}

void client_manager::walk(std::function<void(client&)> f) {
	for (auto& cl : clients) {
		if (!cl)
			continue;

		f(*cl);
	}
}

void client_manager::broadcast(const client* exclude, enet_uint8 channel, ENetPacket* packet) {
	bool err = false;
	bool freed = false;

	for (size_t i = 0; i < clients.size(); i++) {
		auto& cl = clients[i];
		if (!cl || !cl->state || (exclude != nullptr && exclude->cn == cl->cn))
			continue;

		ENetPacket* pkt;
		if (i == clients.size() - 1) {
			pkt = packet;
			freed = true;
		} else {
			pkt = enet_packet_create(packet->data, packet->dataLength, packet->flags & ~ENET_PACKET_FLAG_NO_ALLOCATE);
			if (pkt == nullptr) {
				err = true;
				break;
			}
		}

		enet_peer_send(cl->peer, channel, pkt);
	}

	if (!freed)
		enet_packet_destroy(packet);

	if (err)
		throw std::runtime_error("Failed to create packet");
}

}