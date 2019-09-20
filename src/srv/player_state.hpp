#ifndef SRV_PLAYER_STATE_HPP
#define SRV_PLAYER_STATE_HPP
#include <variant>
#include <cstdint>
#include <map>

#include "../proto/items.hpp"

namespace srv {

class player_state_alive {
public:
	player_state_alive();
	
	bool editing;
	proto::armor armor;
	int32_t armor_health;
	proto::weapon weapon;
	std::map<proto::weapon, int32_t> weapons;
	int32_t health;
	int32_t max_health;
	int32_t quad_time;
};

class player_state_dead {};

class player_state_spectator {};

using player_state = std::variant<player_state_alive, player_state_dead, player_state_spectator>;

}

#endif