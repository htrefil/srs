#include "coop_edit.hpp"

namespace srv {

namespace gm {

coop_edit::coop_edit() {
	spawn_state.weapons[proto::weapon::GL] = 1;
	spawn_state.weapons[proto::weapon::PISTOL] = 40;
}

const player_state_alive& coop_edit::get_spawn_state() const {
	return spawn_state;
}

proto::gamemode coop_edit::get_id() const {
	return proto::gamemode::COOP_EDIT;
}

}

}
