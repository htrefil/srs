#ifndef SRV_SERVER_HPP
#define SRV_SERVER_HPP
#include <enet/enet.h>
#include <string>
#include <cstdlib>

#include "player_state.hpp"
#include "client.hpp"
#include "client_manager.hpp"
#include "../span.hpp"
#include "../proto/writer.hpp"

namespace srv {

class server {
public:
	server(enet_uint16 port, size_t max_clients, std::string description);

	server(const server&) = delete;

	~server();

	void process();

private:
	void handle_connect(client& cl);

	void handle_recv(client& cl, cspan<unsigned char> data);

	void handle_disconnect(client& cl);

	static void write_state(proto::writer& writer, const player_state_spawned& state);

	static void write_resume(proto::writer& writer, const client_manager& manager);

	static void write_init_client(proto::writer& writer, const client& cl);

	client_manager manager;
	std::string description;
	ENetHost* host;
};

}

#endif