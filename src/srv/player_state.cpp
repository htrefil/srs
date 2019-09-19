#include "player_state.hpp"

namespace srv {

player_state_spawned::player_state_spawned() : armor(proto::armor::BLUE), armor_health(100), weapon(proto::weapon::PISTOL), health(100), max_health(100), life_sequence(0), quad_time(0) {
	weapons = {
		{ proto::weapon::SG, 0 },
		{ proto::weapon::CG, 0 },
		{ proto::weapon::RL, 0 },
		{ proto::weapon::RIFLE, 0 },
		{ proto::weapon::GL, 1 },
		{ proto::weapon::PISTOL, 40 },
	};
}

}
