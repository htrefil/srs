#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <cstring>

#include "client.hpp"
#include "../proto/consts.hpp"

namespace srv {

client_info::client_info(std::string name, proto::model model) : name(std::move(name)), model(model), armor(proto::armor::BLUE), armor_health(25), gun(proto::gun::PISTOL), health(100), max_health(100), life_sequence(0) {
	guns = {
		{ proto::gun::SG, 0 },
		{ proto::gun::CG, 0 },
		{ proto::gun::RL, 0 },
		{ proto::gun::RIFLE, 0 },
		{ proto::gun::GL, 1 },
		{ proto::gun::PISTOL, 40 },
	};
}

client::client(ENetPeer* peer, int32_t cn) : peer(peer), cn(cn), address{ 0 } {
	if (enet_address_get_host_ip(&peer->address, address, sizeof(address)) < 0)
		throw std::runtime_error("Failed to get peer IP");	
}

const char* client::name_or_address() const {
	return info ? info->name.c_str() : address;
}

std::string client::id() const {
	return name_or_address() + std::string(" (") + std::to_string(cn) + ")";
}

void client::disconnect(proto::disconnect_reason reason) {
	enet_peer_disconnect(peer, (enet_uint32)reason);
}

void client::disconnect() {
	enet_peer_reset(peer);
}

}