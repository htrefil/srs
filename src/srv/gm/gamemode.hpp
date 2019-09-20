#ifndef SRV_GM_GAMEMODE
#define SRV_GM_GAMEMODE
#include "../client.hpp"
#include "../player_state.hpp"
#include "../../proto/items.hpp"

namespace srv {
namespace gm {

class gamemode {
public:
	virtual ~gamemode();

	virtual const player_state_alive& get_spawn_state() const = 0;

	virtual proto::gamemode get_id() const = 0;
};

}
}

#endif