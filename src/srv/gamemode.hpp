#ifndef SRV_GAMEMODE_HPP
#define SRV_GAMEMODE_HPP
#include "client.hpp"

namespace srv {

class gamemode {
public:
	gamemode(const char* path);

	gamemode(const gamemode&) = delete;

	gamemode(gamemode&& other);

	~gamemode();

	gamemode& operator=(const gamemode&) = delete;

	void join(const client& cl);

	void leave(const client& cl);

	const player_state_alive& get_spawn_state() const;

	proto::gamemode get_id() const;

private:
	struct script_data {
		player_state_alive spawn_state;
	};

	std::optional<script_data> data;
};

}

#endif