#include "gamemode.hpp"

namespace srv {

gamemode::gamemode(const char* path) {}

gamemode::gamemode(gamemode&& other) {}

gamemode::~gamemode() {}

void gamemode::join(const client& cl) {}

void gamemode::leave(const client& cl) {}

const player_state_alive& gamemode::get_spawn_state() const {
	static player_state_alive state;

	return state;
}

proto::gamemode gamemode::get_id() const {
	return proto::gamemode::COOP_EDIT;
}

}