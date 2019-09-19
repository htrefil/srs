#ifndef SRV_CLIENT_MANAGER_HPP
#define SRV_CLIENT_MANAGER_HPP
#include <optional>
#include <vector>
#include <utility>
#include <type_traits>

#include "client.hpp"
#include "../proto/writer.hpp"
#include "../span.hpp"

namespace srv {

// TODO: There must be a better way to do this.
template<bool C, typename T>
struct add_const_if {};

template<typename T>
struct add_const_if<true, T> {
	using type = const T;
};

template<typename T>
struct add_const_if<false, T> {
	using type = T;
};

template<bool C, typename T>
using add_const_if_t = typename add_const_if<C, T>::type;

template<typename T>
class client_iterator {
public:
	using client_type = typename T::value_type;

	bool operator!=(const client_iterator<T>& other) {
		return position != other.position;
	}

	client_iterator<T>& operator++() {
		position++;

		while (position < clients.get_length() && !clients[position])
			position++;

		return *this;
	}

	const client_type& operator*() const {
		return *clients[position];
	}

	add_const_if_t<std::is_const_v<T>, client_type>& operator*() {
		return *clients[position];
	}

private:
	friend class client_manager;

	client_iterator(span<T> clients, size_t position) : clients(clients), position(position) {}

	span<T> clients;
	size_t position;
};

class client_manager {
public:
	using iterator = client_iterator<span<std::optional<client>>>;

	using const_iterator = client_iterator<const span<std::optional<client>>>;

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

	client_iterator<std::optional<client>> begin();

	client_iterator<std::optional<client>> end();	

	client_iterator<const std::optional<client>> begin() const;

	client_iterator<const std::optional<client>> end() const;

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