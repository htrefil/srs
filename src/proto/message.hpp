#ifndef PROTO_MESSAGE_HPP
#define PROTO_MESSAGE_HPP
#include <variant>
#include <string>
#include <cstdint>

#include "consts.hpp"
#include "reader.hpp"
#include "../vector.hpp"

namespace proto {
	
// Client to server.

class cmessage_connect {
public:
	std::string name;
	enum model model;
	std::string password;
	std::string auth_domain;
	std::string auth_name;
};

class cmessage_position {
public:
	// TODO
};

class cmessage_chat {
public:
	std::string text;
};

class cmessage_sound {
public:
	int32_t id;
};

class cmessage_shoot {
public:
	class shot shot;
};

class cmessage_explode {
public:
	class shot shot;
};

class cmessage_sucide {};

class cmessage_try_spawn {};

class cmessage_confirm_spawn {
public:
	int32_t life_sequence;
	enum gun gun;
};

class cmessage_change_weapon {
public:
	enum gun gun;
};

class cmessage_taunt {
public:
};

class cmessage_vote_map {
public:
	std::string name;
	enum gamemode gamemode;
};

using cmessage = std::variant<cmessage_connect, cmessage_position, cmessage_chat>;

}

#endif

// server only
/*
 N_SERVINFO
 N_INITCLIENT
 N_WELCOME
 N_MAPCHANGE
 N_SERVMSG
 N_DAMAGE
 N_HITPUSH
 N_SHOTFX
 N_EXPLODEFX
 N_DIED
 N_SPAWNSTATE
 N_FORCEDEATH
 N_TEAMINFO
 N_ITEMACC
 N_ITEMSPAWN
 N_TIMEUP
 N_CDIS
 N_CURRENTMASTER
 N_PONG
 N_RESUME
 N_BASESCORE
 N_BASEINFO
 N_BASEREGEN
 N_ANNOUNCE
 N_SENDDEMOLIST
 N_SENDDEMO
 N_DEMOPLAYBACK
 N_SENDMAP
 N_DROPFLAG
 N_SCOREFLAG
 N_RETURNFLAG
 N_RESETFLAG
 N_INVISFLAG
 N_CLIENT
 N_AUTHCHAL
 N_INITAI
 N_EXPIRETOKENS
 N_DROPTOKENS
 N_STEALTOKENS
 N_DEMOPACKET */