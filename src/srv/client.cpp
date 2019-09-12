#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <cstring>

#include "client.hpp"
#include "../proto/consts.hpp"

namespace srv {

client_state::client_state(std::string name, proto::model model, game_state gstate) : name(std::move(name)), model(model), gstate(std::move(gstate)) {}

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