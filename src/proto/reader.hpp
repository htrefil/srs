#ifndef PROTO_READER_HPP
#define PROTO_READER_HPP
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "items.hpp"
#include "../span.hpp"

namespace proto {

class read_error : public std::runtime_error {
public:
	read_error(bool size);

	bool is_size() const;

private:
	bool size;
};

class reader {
public:
	reader(span<const unsigned char> data);

	bool ends() const;

	size_t get_offset() const;

	span<const unsigned char> span_from(size_t start, size_t end) const;
	
	template<typename T> 
	std::enable_if_t<std::is_enum_v<T>, T> read() {
		using underlying = std::underlying_type_t<T>;

		auto n = read_basic<underlying>();
		if (n < (underlying)enum_traits<T>::MIN || n > (underlying)enum_traits<T>::MAX)
			throw read_error(false);

		return (T)n;
	}

	template<typename T> 
	std::enable_if_t<!std::is_enum_v<T>, T> read() {
		return read_basic<T>();
	}

	template<typename T>
	T read_basic() {}

private:
	span<const unsigned char> data;
	size_t offset;
};

template<>
unsigned char reader::read_basic();

template<>
bool reader::read_basic();

template<>
int32_t reader::read_basic();

template<>
uint32_t reader::read_basic();

template<>
std::string reader::read_basic();

}
#endif