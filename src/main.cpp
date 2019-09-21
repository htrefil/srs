#include <iostream>
#include <cstdlib>
#include <enet/enet.h>

#include "cpptoml/cpptoml.h"
#include "logger.hpp"

static constexpr auto LOGLEVEL_ERROR = "error"; 
static constexpr auto LOGLEVEL_INFO = "info";
static constexpr auto LOGLEVEL_DEBUG = "debug";

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[1] << " <config path>" << std::endl;
		return EXIT_FAILURE;
	}

	try {
		auto config = cpptoml::parse_file(argv[1]);

		auto port = config->get_qualified_as<enet_uint16>("server.port").value();
		auto max_clients = config->get_qualified_as<size_t>("server.max-clients").value();
		auto description = config->get_qualified_as<std::string>("server.description").value();
		auto loglevel = config->get_qualified_as<std::string>("server.loglevel").value();

		logger::loglevel level;
		if (loglevel == LOGLEVEL_ERROR) {
			level = logger::loglevel::ERROR;
		} else if (loglevel == LOGLEVEL_INFO) {
			level = logger::loglevel::INFO;
		} else if (loglevel == LOGLEVEL_DEBUG) {
			level = logger::loglevel::DEBUG;
		} else {
			logger::get().error() << "Config: Invalid loglevel value: \"" << loglevel << "\"" << std::endl;
			return EXIT_FAILURE;
		}

		logger::get().init(level);

		if (enet_initialize() < 0) {
			logger::get().error() << "Failed to initialize ENet" << std::endl;
			return EXIT_FAILURE;
		}


	}
	catch (const std::bad_optional_access&) {
		logger::get().error() << "Config: A value is missing or has an invalid type" << std::endl;
	} catch (const std::exception& e) {
		logger::get().error() << e.what() << std::endl;
	}

	return EXIT_FAILURE;
}