#ifndef SRV_CLIENT_MANAGER_HPP
#define SRV_CLIENT_MANAGER_HPP
#include <optional>
#include <vector>
#include <utility>

#include "client.hpp"
#include "../proto/writer.hpp"
#include "../span.hpp"

namespace srv {

class client_manager {
public:
	client_manager(size_t max_clients);

	client_manager(const client_manager&) = delete;

	client& add(ENetPeer* peer);

	void remove(client& cl);

	template<typename... Args>
	void write(const client* exclude, enet_uint8 channel, Args... args) {
		if (!packets.empty()) {
			auto& last = packets[packets.size() - 1];

			if (last.exclude == exclude && last.channel == channel) {
				last.writer.write(args...);
				return;
			}
		} else {
			proto::writer writer;
			writer.write(args...);

			packets.push_back(scheduled_packet { exclude, channel, std::move(writer) });
		}
	}

	template<typename... Args>
	void write(enet_uint8 channel, Args... args) {
		write(nullptr, channel, args...);
	}

	template<typename... Args>
	void write_client(const client* exclude, const client& cl, enet_uint8 channel, Args... args) {
		proto::writer writer;
		writer.write(args...);

		auto data = writer.get_data();

		write(exclude, channel, proto::message::CLIENT, cl.cn, (uint32_t)data.get_length(), data);
	}

	template<typename... Args>
	void write_client(const client& cl, enet_uint8 channel, Args... args) {
		write_client(nullptr, cl, channel, args...);
	}

	void flush();

	void walk(std::function<void(const client&)> f) const;

	void walk(std::function<void(client&)> f);

private:
	struct scheduled_packet {
		const client* exclude;
		enet_uint8 channel;
		proto::writer writer;
	};

	void broadcast(const client* exclude, enet_uint8 channel, ENetPacket* packet);

	std::vector<std::optional<client>> clients;
	std::vector<scheduled_packet> packets;
};

}

#endif