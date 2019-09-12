#ifndef SRV_CLIENT_HPP
#define SRV_CLIENT_HPP
#include <string>
#include <variant>
#include <optional>
#include <map>
#include <enet/enet.h>
#include <vector>
#include <utility>

#include "game_state.hpp"
#include "../proto/items.hpp"
#include "../proto/consts.hpp"
#include "../proto/writer.hpp"

namespace srv {

enum class disconnect_reason : enet_uint8 {
	NONE = proto::DISCONNECT_NORMAL,
	MESSAGE = proto::DISCONNECT_MESSAGE_ERROR,
	SIZE = proto::DISCONNECT_END_OF_PACKET,
	TIMEOUT = proto::DISCONNECT_TIMEOUT,
};

class client_state {
public:
	client_state(std::string name, proto::model model, game_state gstate);

	std::string name;
	proto::model model;
	game_state gstate;
};

class client {
public:
	client(ENetPeer* peer, int32_t cn);

	client(const client&) = delete;

	client(client&& other) = default;

	client& operator=(client&& other) = default;

	const char* name_or_address() const;

	std::string id() const;

	template<typename... Args>
	void write(enet_uint8 channel, Args... args) {
		if (!packets.empty()) {
			auto& last = packets[packets.size() - 1];
			
			if (last.channel == channel) {
				last.writer.write(args...);
				return;
			}
		} else {
			proto::writer writer;
			writer.write(args...);

			packets.push_back(scheduled_packet { channel, std::move(writer) });	
		}
	}

	void disconnect(disconnect_reason reason);

	void disconnect();

	ENetPeer* peer;
	int32_t cn;
	char address[15 + 1];
	std::optional<client_state> state;
private:
	friend class client_manager;

	struct scheduled_packet {
		enet_uint8 channel;
		proto::writer writer;
	};

	std::vector<scheduled_packet> packets;
};

}

#endif