#include <cassert>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <cstring>

#include "client.hpp"
#include "../proto/consts.hpp"

namespace srv {

client_info::client_info(std::string name, proto::model model) : name(std::move(name)), player_state(proto::player_state::ALIVE), model(model), armor(proto::armor::BLUE), armor_health(25), weapon(proto::weapon::PISTOL), health(100), max_health(100), life_sequence(0), quad_time(0), frags(0) {
	weapons = {
		{ proto::weapon::SG, 0 },
		{ proto::weapon::CG, 0 },
		{ proto::weapon::RL, 0 },
		{ proto::weapon::RIFLE, 0 },
		{ proto::weapon::GL, 1 },
		{ proto::weapon::PISTOL, 40 },
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