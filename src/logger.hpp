#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <ostream>
#include <optional>

#include "singleton.hpp"

class logger : public singleton<logger> {
public:
	enum class loglevel {
		ERROR,
		INFO,
		DEBUG,
	};

	logger() = default;

	logger(const logger&) = delete;

	void init(loglevel level);

	std::ostream& error();

	std::ostream& info();

	std::ostream& debug();

private:
	std::ostream& log();

	loglevel level;
};

#endif