#include "gamemode.hpp"

namespace srv {

gamemode::~gamemode() {}

gamemode_coop_edit::gamemode_coop_edit() {
	spawn_state.weapons[proto::weapon::GL] = 1;
	spawn_state.weapons[proto::weapon::PISTOL] = 40;
}

const player_state_spawned& gamemode_coop_edit::get_spawn_state() const {
	return spawn_state;
}

proto::gamemode gamemode_coop_edit::get_id() const {
	return proto::gamemode::COOP_EDIT;
}

}