#include "reader.hpp"
#include "strings.hpp"
#include "consts.hpp"
#include "items.hpp"
#include "../utf8/utf8.h"

namespace proto {

read_error::read_error(bool size) : std::runtime_error(size ? "Reached end of stream" : "Invalid data"), size(size) {}

bool read_error::is_size() const {
	return size;
}

reader::reader(span<const unsigned char> data) : data(data), offset(0) {}

bool reader::ends() const {
	return offset >= data.get_length();
}

size_t reader::get_offset() const {
	return offset;
}

span<const unsigned char> reader::span_from(size_t start, size_t end) const {
	return data.sub(start, end);
}

template<>
unsigned char reader::read_basic() {
	if (offset >= data.get_length()) 
		throw read_error(true);

	return data[offset++];
}

template<>
bool reader::read_basic() {
	auto b = read<unsigned char>();
	switch (b) {
		case 0:
			return false;

		case 1:
			return true;

		default:
			throw read_error(false);
	}
}

template<>
int32_t reader::read_basic() {
	auto b = read<unsigned char>();

	switch (b) {
		case 0x80: {
			auto c = read<unsigned char>();
			auto d = read<unsigned char>();

			return (int32_t)c + ((int32_t)d << 8);
		}

		case 0x81: {
			auto c = read<unsigned char>();
			auto d = read<unsigned char>();
			auto e = read<unsigned char>();
			auto f = read<unsigned char>();

			return (int32_t)c + ((int32_t)d << 8) + ((int32_t)e << 16) + ((int32_t)f << 24);
		}

		default:
			return (int32_t)b;
	}
}

template<>
uint32_t reader::read_basic() {
	auto n = (uint32_t)read<unsigned char>();

	if ((n & (1 << 7)) != 0) 
		n += (((uint32_t)read<unsigned char>()) << 7) - (1 << 7);

	if ((n & (1 << 14)) != 0) 
		n += (((uint32_t)read<unsigned char>()) << 14) - (1 << 14);

	if ((n & (1 << 21)) != 0) 
		n += (((uint32_t)read<unsigned char>()) << 14) - (1 << 14);	

	if ((n & (1 << 28)) != 0) 
		n += 0x0F << 24;

	return n;
}

template<>
std::string reader::read_basic() {
	std::string result;
	while (true) {
		auto n = read<int32_t>();
		if (n == 0)
			return result;

		auto c = decode(n);
		if (!c)
			throw read_error(false);

		char buffer[UTF8_MAX_ENCODED_LENGTH + 1] = { 0 };
		utf8_encode(buffer, *c);

		result += buffer;
	}
}

}