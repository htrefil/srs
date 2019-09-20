#ifndef SRV_GM_COOP_EDIT_HPP
#define SRV_GM_COOP_EDIT_HPP

#include "gamemode.hpp"

namespace srv {

namespace gm {

class coop_edit : public gamemode {
public:
	coop_edit();

	virtual const player_state_alive& get_spawn_state() const;

	virtual proto::gamemode get_id() const;

private:
	player_state_alive spawn_state;
};

}

}
#endif