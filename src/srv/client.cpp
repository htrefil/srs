#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <cstring>

#include "client.hpp"
#include "../proto/consts.hpp"

namespace srv {

client_state::client_state(std::string name, proto::model model) : name(std::move(name)), model(model), armor(proto::armor::BLUE) {
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
	return state ? state->name.c_str() : address;
}

std::string client::id() const {
	return name_or_address() + std::string(" (") + std::to_string(cn) + ")";
}

void client::disconnect(disconnect_reason reason) {
	enet_peer_disconnect(peer, (enet_uint32)reason);
}

void client::disconnect() {
	enet_peer_reset(peer);
}

}