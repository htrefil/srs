#ifndef PROTO_CONSTS_HPP
#define PROTO_CONSTS_HPP
#include <cstdint>
#include <enet/enet.h>

namespace proto {

static constexpr int32_t PROTOCOL_VERSION = 259;

static constexpr enet_uint8 CHANNEL_POSITIONS = 0;
static constexpr enet_uint8 CHANNEL_MESSAGES = 1;
static constexpr enet_uint8 CHANNEL_FILES = 2;

static constexpr auto DMF = 16.0f;
static constexpr auto DNF = 100.0f;

}
#endif
