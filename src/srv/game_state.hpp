#ifndef SRV_GAME_STATE_HPP
#define SRV_GAME_STATE_HPP
#include <map>
#include <cstdint>
#include <string>
#include <variant>

#include "../proto/items.hpp"

namespace srv {

class game_state_dead {};

class game_state_spectator {};

class game_state_spawned {
public:
	game_state_spawned();

	proto::armor armor;
	int32_t armor_health;
	proto::gun gun;
	std::map<proto::gun, int32_t> guns;
	int32_t health;
	int32_t max_health;
	int32_t life_sequence;
	std::string team;
};

using game_state = std::variant<game_state_dead, game_state_spectator, game_state_spawned>;

}

#endif