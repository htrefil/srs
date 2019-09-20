#ifndef SRV_GAMEMODE_HPP
#define SRV_GAMEMODE_HPP
#include "client.hpp"
#include "../proto/items.hpp"

namespace srv {
	
class gamemode {
public:
	virtual ~gamemode();

	virtual const player_state_alive& get_spawn_state() const = 0;

	virtual proto::gamemode get_id() const = 0;
};

class gamemode_coop_edit : public gamemode {
public:
	gamemode_coop_edit();

	virtual const player_state_alive& get_spawn_state() const;

	virtual proto::gamemode get_id() const;

private:
	player_state_alive spawn_state;
};

}

#endif