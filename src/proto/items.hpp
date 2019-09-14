#ifndef PROTO_ITEMS_HPP
#define PROTO_ITEMS_HPP
#include <cstdint>
#include <vector>
#include <enet/enet.h>

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

enum class message : int32_t {
	CONNECT = 0,
	SERVER_INFO,
	WELCOME,
	INIT_CLIENT,
	POSITION,
	CHAT_MESSAGE,
	SOUND,
	LEAVE,
	SHOOT,
	EXPLODE,
	SUICIDE,
	DIED,
	DAMAGE,
	HIT_PUSH,
	SHOT_EFFECTS,
	EXPLODE_EFFECTS,
	TRY_SPAWN,
	SPAWN_STATE,
	CONFIRM_SPAWN,
	FORCE_DEATH,
	CHANGE_WEAPON,
	TAUNT,
	MAP_CHANGE,
	VOTE_MAP,
	TEAM_INFO,
	ITEM_SPAWN,
	ITEM_PICKUP,
	ITEM_ACC,
	TELEPORT,
	JUMP_PAD,
	PING,
	PONG,
	CLIENT_PING,
	TIME_LEFT,
	FORCE_INTERMISSION,
	SERVER_MESSAGE,
	ITEM_LIST,
	RESUME,
	EDIT_MODE,
	EDIT_ENT,
	EDIT_F,
	EDIT_T,
	EDIT_M,
	FLIP,
	COPY,
	PASTE,
	ROTATE,
	REPLACE,
	DEL_CUBE,
	REMIP,
	NEW_MAP,
	GET_MAP,
	SEND_MAP,
	CLIPBOARD,
	EDIT_VAR,
	MASTER_MODE,
	KICK,
	CLEAR_BANS,
	CURRENT_MASTER,
	SPECTATOR,
	SET_MASTER,
	SET_TEAM,
	BASES,
	BASE_INFO,
	BASE_SCORE,
	REP_AMMO,
	BASE_REGEN,
	ANNOUNCE,
	LIST_DEMOS,
	SEND_DEMO_LIST,
	GET_DEMO,
	SEND_DEMO,
	DEMO_PLAYBACK,
	RECORD_DEMO,
	STOP_DEMO,
	CLEAR_DEMOS,
	TAKE_FLAG,
	RETURN_FLAG,
	RESET_FLAG,
	INVISIBLE_FLAG,
	TRY_DROP_FLAG,
	DROP_FLAG,
	SCORE_FLAG,
	INIT_FLAGS,
	TEAM_CHAT_MESSAGE,
	CLIENT,
	AUTH_TRY,
	AUTH_KICK,
	AUTH_CHALLENGE,
	AUTH_ANSWER,
	REQUEST_AUTH,
	PAUSE_GAME,
	GAME_SPEED,
	ADD_BOT,
	DEL_BOT,
	INIT_AI,
	FROM_AI,
	BOT_LIMIT,
	BOT_BALANCE,
	MAP_CRC,
	CHECK_MAPS,
	CHANGE_NAME,
	CHANGE_MODEL,
	CHANGE_TEAM,
	INIT_TOKENS,
	TAKE_TOKEN,
	EXPIRE_TOKENS,
	DROP_TOKENS,
	DEPOSIT_TOKENS,
	STEAL_TOKENS,
	SERVER_COMMAND,
	DEMO_MESSAGE,
};

enum class player_state : uint32_t {
	ALIVE = 0,
	DEAD,
	SPAWNING,
	EDITING,
	SPECTATOR,
};

enum class disconnect_reason : enet_uint32 {
	NONE = 0,
	END_OF_PACKET,
	LOCAL_MODE,
	KICK,
	MESSAGE_ERROR,
	IP_BAN,
	PRIVATE_MODE,
	MAX_CLIENTS,
	TIMEOUT,
	OVERFLOW,
	PASSWORD,	
};


template<typename T>
struct enum_traits {};

template<>
struct enum_traits<gun> {
	static constexpr auto MIN = gun::FIST;
	static constexpr auto MAX = gun::PISTOL;
};

template<>
struct enum_traits<model> {
	static constexpr auto MIN = model::MR_FIXIT;
	static constexpr auto MAX = model::CANNON;
};

template<>
struct enum_traits<gamemode> {
	static constexpr auto MIN = gamemode::FFA;
	static constexpr auto MAX = gamemode::EFFICIENCY_COLLECT;
};

template<>
struct enum_traits<armor> {
	static constexpr auto MIN = armor::BLUE;
	static constexpr auto MAX = armor::YELLOW;
};

template<>
struct enum_traits<message> {
	static constexpr auto MIN = message::CONNECT;
	static constexpr auto MAX = message::DEMO_MESSAGE;
};

template<>
struct enum_traits<player_state> {
	static constexpr auto MIN = player_state::ALIVE;
	static constexpr auto MAX = player_state::SPECTATOR;
};

}

#endif