#include "game_state.hpp"

namespace srv {

game_state_spawned::game_state_spawned() : armor(proto::armor::BLUE), armor_health(100), gun(proto::gun::PISTOL), health(100), max_health(100), life_sequence(100) {
	guns = {
		{ proto::gun::SG, 0 },
		{ proto::gun::CG, 0 },
		{ proto::gun::RL, 0 },
		{ proto::gun::RIFLE, 0 },
		{ proto::gun::GL, 1 },
		{ proto::gun::PISTOL, 40 },
	};
}

}