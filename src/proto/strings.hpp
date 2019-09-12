#ifndef PROTO_STRINGS_HPP
#define PROTO_STRINGS_HPP
#include <optional>

#include "../utf8/utf8.h"

namespace proto {

std::optional<int32_t> encode(rune_t c);

std::optional<rune_t> decode(int32_t c);

}

#endif