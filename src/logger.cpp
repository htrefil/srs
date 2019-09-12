#include <iostream>

#include "logger.hpp"

class nop_buffer : public std::streambuf {
public:
	int overflow(int c) {
		return c;
	}
};

static std::ostream& nop_stream() {
	static nop_buffer buffer;
	static std::ostream stream(&buffer);

	return stream;
}

void logger::init(std::optional<bool> level) {
	this->level = level;
}

std::ostream& logger::error() {
	return std::cout << "[err] ";
}

std::ostream& logger::info() {
	return level ? std::cout << "[inf] " : nop_stream();
}

std::ostream& logger::debug() {
	return level && *level ? std::cout << "[dbg] " : nop_stream();
}

