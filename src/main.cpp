#include <iostream>
#include <cstdlib>
#include <exception>
#include <enet/enet.h>
#include <optional>
#include <cstring>
#include <memory>
#include <functional>
#include <variant>

#include "cpptoml/cpptoml.h"
#include "srv/server.hpp"
#include "logger.hpp"

template<typename T>
static T must_get(cpptoml::table& table, const char* name) {
	auto value = table.get_qualified_as<T>(name);
	if (!value)
		throw std::runtime_error("Config: Value " + std::string(name) + " is missing or has an invalid type");

	return *value;
}

static std::optional<bool> parse_loglevel(const char* level) {
	if (strcmp(level, "none") == 0)
		return {};

	if (strcmp(level, "info") == 0)
		return false;

	if (strcmp(level, "debug") == 0)
		return true;

	throw std::runtime_error("Config: Invalid loglevel value \"" + std::string(level) + "\"");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: srs <config path>" << std::endl;
		return EXIT_FAILURE;
	}

	try {
		auto config = cpptoml::parse_file(argv[1]);

		auto port = must_get<enet_uint16>(*config, "server.port");
		auto max_clients = must_get<size_t>(*config, "server.max-clients");
		auto description = must_get<std::string>(*config, "server.description");
		auto level = parse_loglevel(must_get<std::string>(*config, "server.loglevel").c_str());

		logger::get().init(level);

		if (enet_initialize() < 0) {
			logger::get().error() << "Error: Failed to initialize ENet" << std::endl;
			return EXIT_FAILURE;
		}

		srv::server server(port, max_clients, description);

		logger::get().info() << "Listening on port " << port << std::endl;

		while (true)
			server.process();
	} 
	catch (const cpptoml::parse_exception& e) {
		logger::get().error() << "Config: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		logger::get().error() << e.what() << std::endl;
	}
	
	return EXIT_FAILURE;
}

