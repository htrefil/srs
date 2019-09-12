#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <ostream>
#include <optional>

#include "singleton.hpp"

class logger : public singleton<logger> {
public:
	logger() = default;

	logger(const logger&) = delete;

	void init(std::optional<bool> level);

	std::ostream& error();

	std::ostream& info();

	std::ostream& debug();

private:
	std::ostream& log();

	std::optional<bool> level;
};

#endif