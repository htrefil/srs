#ifndef SRV_CLIENT_HPP
#define SRV_CLIENT_HPP
#include <string>
#include <variant>
#include <optional>
#include <map>
#include <enet/enet.h>
#include <vector>
#include <utility>

#include "player_state.hpp"
#include "../proto/items.hpp"
#include "../proto/consts.hpp"
#include "../proto/writer.hpp"

namespace srv {

class client_info {
public:
	client_info(std::string name, std::string team, proto::model model, player_state state);

	std::string name;
	std::string team;
	proto::model model;
	player_state state;
	int32_t life_sequence;
	int32_t frags;
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

	void disconnect(proto::disconnect_reason reason);

	void disconnect();

	ENetPeer* peer;
	int32_t cn;
	char address[15 + 1];
	std::optional<client_info> info;
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