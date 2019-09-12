#ifndef PROTO_ITEMS_HPP
#define PROTO_ITEMS_HPP
#include <cstdint>
#include <vector>

#include "../vector.hpp"

namespace proto {

enum class gun : int32_t {
	FIST = 0,
	SG,
	CG,
	RL,
	RIFLE,
	GL,
	PISTOL
};

enum class model : int32_t {
	MR_FIXIT = 0,
	SNOUTX10K,
	OGRO,
	INKY,
	CANNON,
};

enum class gamemode : int32_t {
	FFA = 0,
	COOP_EDIT,
	TEAMPLAY,
	INSTAGIB,
	INSTA_TEAM,
	EFFICIENCY,
	EFFICIENCY_TEAM,
	TACTICS,
	TACTICS_TEAM,
	CAPTURE,
	REGEN_CAPTURE,
	CTF,
	INSTAGIB_CTF,
	PROTECT,
	INSTAGIB_PROTECT,
	HOLD,
	INSTAGIB_HOLD,
	EFFICIENCY_CTF,
	EFFICIENCY_PROTECT,
	EFFICIENCY_HOLD,
	COLLECT,
	INSTAGIB_COLLECT,
	EFFICIENCY_COLLECT,
};

enum class armor : int32_t {
	BLUE = 0,
	GREEN,
	YELLOW,
};

class hit {
public:
	int32_t target;
	int32_t life_sequence;
	float distance;
	int32_t rays;
	vector direction;
};

class shot {
public:
	int32_t id;
	enum gun gun;
	vector from;
	vector to;
	std::vector<hit> hits;
};

}

#endif