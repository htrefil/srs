#ifndef PROTO_CONSTS_HPP
#define PROTO_CONSTS_HPP
#include <cstdint>
#include <enet/enet.h>

namespace proto {

static constexpr int32_t PROTOCOL_VERSION = 259;

static constexpr enet_uint8 CHANNEL_POSITIONS = 0;
static constexpr enet_uint8 CHANNEL_MESSAGES = 1;
static constexpr enet_uint8 CHANNEL_FILES = 2;

static constexpr enet_uint32 DISCONNECT_NORMAL = 0;
static constexpr enet_uint32 DISCONNECT_END_OF_PACKET = 1;
static constexpr enet_uint32 DISCONNECT_LOCAL_MODE = 2;
static constexpr enet_uint32 DISCONNECT_KICK = 3;
static constexpr enet_uint32 DISCONNECT_MESSAGE_ERROR = 4;
static constexpr enet_uint32 DISCONNECT_IP_BAN = 5;
static constexpr enet_uint32 DISCONNECT_PRIVATE_MODE = 6;
static constexpr enet_uint32 DISCONNECT_MAX_CLIENTS = 7;
static constexpr enet_uint32 DISCONNECT_TIMEOUT = 8;
static constexpr enet_uint32 DISCONNECT_OVERFLOW = 9;
static constexpr enet_uint32 DISCONNECT_PASSWORD = 10;

static constexpr int32_t MESSAGE_CONNECT = 0;
static constexpr int32_t MESSAGE_SERVER_INFO = 1;
static constexpr int32_t MESSAGE_WELCOME = 2;
static constexpr int32_t MESSAGE_INIT_CLIENT = 3;
static constexpr int32_t MESSAGE_POSITION = 4;
static constexpr int32_t MESSAGE_CHAT_MESSAGE = 5;
static constexpr int32_t MESSAGE_SOUND = 6;
static constexpr int32_t MESSAGE_LEAVE = 7;
static constexpr int32_t MESSAGE_SHOOT = 8;
static constexpr int32_t MESSAGE_EXPLODE = 9;
static constexpr int32_t MESSAGE_SUICIDE = 10;
static constexpr int32_t MESSAGE_DIED = 11;
static constexpr int32_t MESSAGE_DAMAGE = 12;
static constexpr int32_t MESSAGE_HIT_PUSH = 13;
static constexpr int32_t MESSAGE_SHOT_EFFECTS = 14;
static constexpr int32_t MESSAGE_EXPLODE_EFFECTS = 15;
static constexpr int32_t MESSAGE_TRY_SPAWN = 16;
static constexpr int32_t MESSAGE_SPAWN_STATE = 17;
static constexpr int32_t MESSAGE_CONFIRM_SPAWN = 18;
static constexpr int32_t MESSAGE_FORCE_DEATH = 19;
static constexpr int32_t MESSAGE_CHANGE_WEAPON = 20;
static constexpr int32_t MESSAGE_TAUNT = 21;
static constexpr int32_t MESSAGE_MAP_CHANGE = 22;
static constexpr int32_t MESSAGE_VOTE_MAP = 23;
static constexpr int32_t MESSAGE_TEAM_INFO = 24;
static constexpr int32_t MESSAGE_ITEM_SPAWN = 25;
static constexpr int32_t MESSAGE_ITEM_PICKUP = 26;
static constexpr int32_t MESSAGE_ITEM_ACC = 27;
static constexpr int32_t MESSAGE_TELEPORT = 28;
static constexpr int32_t MESSAGE_JUMP_PAD = 29;
static constexpr int32_t MESSAGE_PING = 30;
static constexpr int32_t MESSAGE_PONG = 31;
static constexpr int32_t MESSAGE_CLIENT_PING = 32;
static constexpr int32_t MESSAGE_TIME_LEFT = 33;
static constexpr int32_t MESSAGE_FORCE_INTERMISSION = 34;
static constexpr int32_t MESSAGE_SERVER_MESSAGE = 35;
static constexpr int32_t MESSAGE_ITEM_LIST = 36;
static constexpr int32_t MESSAGE_RESUME = 37;
static constexpr int32_t MESSAGE_EDIT_MODE = 38;
static constexpr int32_t MESSAGE_EDIT_ENT = 39;
static constexpr int32_t MESSAGE_EDIT_F = 40;
static constexpr int32_t MESSAGE_EDIT_T = 41;
static constexpr int32_t MESSAGE_EDIT_M = 42;
static constexpr int32_t MESSAGE_FLIP = 43;
static constexpr int32_t MESSAGE_COPY = 44;
static constexpr int32_t MESSAGE_PASTE = 45;
static constexpr int32_t MESSAGE_ROTATE = 46;
static constexpr int32_t MESSAGE_REPLACE = 47;
static constexpr int32_t MESSAGE_DEL_CUBE = 48;
static constexpr int32_t MESSAGE_REMIP = 49;
static constexpr int32_t MESSAGE_NEW_MAP = 50;
static constexpr int32_t MESSAGE_GET_MAP = 51;
static constexpr int32_t MESSAGE_SEND_MAP = 52;
static constexpr int32_t MESSAGE_CLIPBOARD = 53;
static constexpr int32_t MESSAGE_EDIT_VAR = 54;
static constexpr int32_t MESSAGE_MASTER_MODE = 55;
static constexpr int32_t MESSAGE_KICK = 56;
static constexpr int32_t MESSAGE_CLEAR_BANS = 57;
static constexpr int32_t MESSAGE_CURRENT_MASTER = 58;
static constexpr int32_t MESSAGE_SPECTATOR = 59;
static constexpr int32_t MESSAGE_SET_MASTER = 60;
static constexpr int32_t MESSAGE_SET_TEAM = 61;
static constexpr int32_t MESSAGE_BASES = 62;
static constexpr int32_t MESSAGE_BASE_INFO = 63;
static constexpr int32_t MESSAGE_BASE_SCORE = 64;
static constexpr int32_t MESSAGE_REP_AMMO = 65;
static constexpr int32_t MESSAGE_BASE_REGEN = 66;
static constexpr int32_t MESSAGE_ANNOUNCE = 67;
static constexpr int32_t MESSAGE_LIST_DEMOS = 68;
static constexpr int32_t MESSAGE_SEND_DEMO_LIST = 69;
static constexpr int32_t MESSAGE_GET_DEMO = 70;
static constexpr int32_t MESSAGE_SEND_DEMO = 71;
static constexpr int32_t MESSAGE_DEMO_PLAYBACK = 72;
static constexpr int32_t MESSAGE_RECORD_DEMO = 73;
static constexpr int32_t MESSAGE_STOP_DEMO = 74;
static constexpr int32_t MESSAGE_CLEAR_DEMOS = 75;
static constexpr int32_t MESSAGE_TAKE_FLAG = 76;
static constexpr int32_t MESSAGE_RETURN_FLAG = 77;
static constexpr int32_t MESSAGE_RESET_FLAG = 78;
static constexpr int32_t MESSAGE_INVISIBLE_FLAG = 79;
static constexpr int32_t MESSAGE_TRY_DROP_FLAG = 80;
static constexpr int32_t MESSAGE_DROP_FLAG = 81;
static constexpr int32_t MESSAGE_SCORE_FLAG = 82;
static constexpr int32_t MESSAGE_INIT_FLAGS = 83;
static constexpr int32_t MESSAGE_TEAM_CHAT_MESSAGE = 84;
static constexpr int32_t MESSAGE_CLIENT = 85;
static constexpr int32_t MESSAGE_AUTH_TRY = 86;
static constexpr int32_t MESSAGE_AUTH_KICK = 87;
static constexpr int32_t MESSAGE_AUTH_CHALLENGE = 88;
static constexpr int32_t MESSAGE_AUTH_ANSWER = 89;
static constexpr int32_t MESSAGE_REQUEST_AUTH = 90;
static constexpr int32_t MESSAGE_PAUSE_GAME = 91;
static constexpr int32_t MESSAGE_GAME_SPEED = 92;
static constexpr int32_t MESSAGE_ADD_BOT = 93;
static constexpr int32_t MESSAGE_DEL_BOT = 94;
static constexpr int32_t MESSAGE_INIT_AI = 95;
static constexpr int32_t MESSAGE_FROM_AI = 96;
static constexpr int32_t MESSAGE_BOT_LIMIT = 97;
static constexpr int32_t MESSAGE_BOT_BALANCE = 98;
static constexpr int32_t MESSAGE_MAP_CRC = 99;
static constexpr int32_t MESSAGE_CHECK_MAPS = 100;
static constexpr int32_t MESSAGE_CHANGE_NAME = 101;
static constexpr int32_t MESSAGE_CHANGE_MODEL = 102;
static constexpr int32_t MESSAGE_CHANGE_TEAM = 103;
static constexpr int32_t MESSAGE_INIT_TOKENS = 104;
static constexpr int32_t MESSAGE_TAKE_TOKEN = 105;
static constexpr int32_t MESSAGE_EXPIRE_TOKENS = 106;
static constexpr int32_t MESSAGE_DROP_TOKENS = 107;
static constexpr int32_t MESSAGE_DEPOSIT_TOKENS = 108;
static constexpr int32_t MESSAGE_STEAL_TOKENS = 109;
static constexpr int32_t MESSAGE_SERVER_COMMAND = 110;
static constexpr int32_t MESSAGE_DEMO_MESSAGE = 111;

static constexpr auto DMF = 16.0f;
static constexpr auto DNF = 100.0f;

}
#endif

/*

N_CONNECT = 0
N_SERVINFO = 1
N_WELCOME = 2
N_INITCLIENT = 3
N_POS = 4
N_TEXT = 5
N_SOUND  = 6
N_CDIS = 7
N_SHOOT = 8
N_EXPLODE = 9
N_SUICIDE = 10
N_DIED = 11
N_DAMAGE = 12
N_HITPUSH = 13
N_SHOTFX = 14
N_EXPLODEFX = 15
N_TRYSPAWN = 16
N_SPAWNSTATE = 17
N_SPAWN = 18
N_FORCEDEATH = 19
N_GUNSELECT = 20
N_TAUNT = 21
N_MAPCHANGE = 22
N_MAPVOTE = 23
N_TEAMINFO = 24
N_ITEMSPAWN = 25
N_ITEMPICKUP = 26
N_ITEMACC = 27
N_TELEPORT = 28
N_JUMPPAD = 29
N_PING = 30
N_PONG = 31
N_CLIENTPING = 32
N_TIMEUP = 33
N_FORCEINTERMISSION = 34
N_SERVMSG = 35
N_ITEMLIST = 36
N_RESUME = 37
N_EDITMODE = 38
N_EDITENT = 39
N_EDITF = 40
N_EDITT = 41
N_EDITM = 42
N_FLIP = 43
N_COPY = 44
N_PASTE = 45
N_ROTATE = 46
N_REPLACE = 47
N_DELCUBE = 48
N_REMIP = 49
N_NEWMAP = 50
N_GETMAP = 51
N_SENDMAP = 52
N_CLIPBOARD = 53
N_EDITVAR = 54
N_MASTERMODE = 55
N_KICK = 56
N_CLEARBANS = 57
N_CURRENTMASTER = 58
N_SPECTATOR = 59
N_SETMASTER = 60
N_SETTEAM = 61
N_BASES = 62
N_BASEINFO = 63
N_BASESCORE = 64
N_REPAMMO = 65
N_BASEREGEN = 66
N_ANNOUNCE = 67
N_LISTDEMOS = 68
N_SENDDEMOLIST = 69
N_GETDEMO = 70
N_SENDDEMO = 71
N_DEMOPLAYBACK = 72
N_RECORDDEMO = 73
N_STOPDEMO = 74
N_CLEARDEMOS = 75
N_TAKEFLAG = 76
N_RETURNFLAG = 77
N_RESETFLAG = 78
N_INVISFLAG = 79
N_TRYDROPFLAG = 80
N_DROPFLAG = 81
N_SCOREFLAG = 82
N_INITFLAGS = 83
N_SAYTEAM = 84
N_CLIENT = 85
N_AUTHTRY = 86
N_AUTHKICK = 87
N_AUTHCHAL = 88
N_AUTHANS = 89
N_REQAUTH = 90
N_PAUSEGAME = 91
N_GAMESPEED = 92
N_ADDBOT = 93
N_DELBOT = 94
N_INITAI = 95
N_FROMAI = 96
N_BOTLIMIT = 97
N_BOTBALANCE = 98
N_MAPCRC = 99
N_CHECKMAPS = 100
N_SWITCHNAME = 101
N_SWITCHMODEL = 102
N_SWITCHTEAM = 103
N_INITTOKENS = 104
N_TAKETOKEN = 105
N_EXPIRETOKENS = 106
N_DROPTOKENS = 107
N_DEPOSITTOKENS = 108
N_STEALTOKENS = 109
N_SERVCMD = 110
N_DEMOPACKET = 111

*/