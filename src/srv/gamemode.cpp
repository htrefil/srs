#include <stdexcept>
#include <lauxlib.h>
#include <lualib.h>
#include <lstate.h>

#include "gamemode.hpp"
#include "../logger.hpp"

namespace srv {

gamemode::gamemode(const char* path) {
	// Here we are abusing the `ud` parameter, intended as data for the allocator, to pass our instance of the class.
	state = 
		lua_newstate([](void* userdata, void* ptr, size_t old_size, size_t new_size) -> void* {
			if (new_size == 0) {
				free(ptr);
				return NULL;
			}

			return realloc(ptr, new_size);
		}, this);

	if (state == nullptr)
		throw std::runtime_error("Failed to create Lua state");

	static const luaL_Reg FUNCTIONS[] = {
		{ "setup", setup, },
		{ nullptr, nullptr, },
	};

	luaL_openlibs(state);
	luaL_newlib(state, FUNCTIONS);
	lua_setglobal(state, "server");

	try {
		if (luaL_dofile(state, path))
			throw std::runtime_error("Failed to execute Lua script: " + std::string(lua_tostring(state, 1)));

		if (!data)
			throw std::runtime_error("Lua script didn\'t initialize");
	} catch (...) {
		lua_close(state);
		throw;
	}
}

gamemode::gamemode(gamemode&& other) : state(other.state) {
	other.state = nullptr;
}

gamemode::~gamemode() {
	if (state != nullptr)
		lua_close(state);
}

void gamemode::join(const client& cl) {}

void gamemode::leave(const client& cl) {}

const player_state_alive& gamemode::get_spawn_state() const {
	return data->spawn_state;
}

proto::gamemode gamemode::get_id() const {
	return data->gamemode;
}

int gamemode::setup(lua_State* state) {
	auto& self = *(gamemode*)state->l_G->ud;

	if (!lua_istable(state, 1))
		return luaL_error(state, "Expected a table");

	lua_pushnil(state);
	while (lua_next(state, 1) != 0) {
		lua_pushvalue(state, -2);

		auto key = lua_tostring(state, -1);
		auto value = lua_tostring(state, -2);

		lua_pop(state, 2);
		
		logger::get().debug() << key << " - " << value << std::endl;
	}

	return 1;
}

}