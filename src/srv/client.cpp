#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <cstring>

#include "client.hpp"
#include "../proto/consts.hpp"

namespace srv {

client_info::client_info(std::string name, std::string team, proto::model model, player_state state) : name(name), team(team), model(model), state(state), frags(0) {}

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