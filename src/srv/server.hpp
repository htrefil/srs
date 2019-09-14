#ifndef SRV_SERVER_HPP
#define SRV_SERVER_HPP
#include <enet/enet.h>
#include <string>
#include <cstdlib>

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

	void handle_recv(client& cl, span<unsigned char> data);

	void handle_disconnect(client& cl);

	static void write_state(proto::writer& writer, const client_info& info);

	client_manager manager;
	std::string description;
	ENetHost* host;
};

}

#endif