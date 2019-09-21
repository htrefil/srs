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

logger::logger() : level(loglevel::INFO) {}

void logger::init(loglevel level) {
	this->level = level;
}

std::ostream& logger::error() {
	return std::cout << "[err] ";
}

std::ostream& logger::info() {
	return level == loglevel::INFO || level == loglevel::DEBUG ? std::cout << "[inf] " : nop_stream();
}

std::ostream& logger::debug() {
	return level == loglevel::DEBUG ? std::cout << "[dbg] " : nop_stream();
}

