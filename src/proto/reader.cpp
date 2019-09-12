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

reader::reader(span<unsigned char> data) : data(data), offset(0) {}

bool reader::ends() const {
	return offset >= data.get_length();
}

size_t reader::get_offset() const {
	return offset;
}

span<unsigned char> reader::span_from(size_t start, size_t end) const {
	return data.sub(start, end);
}

unsigned char reader::read_byte() {
	if (offset >= data.get_length()) 
		throw read_error(true);

	return data[offset++];
}

template<> 
int32_t reader::read() {
	auto b = read_byte();

	switch (b) {
		case 0x80: {
			auto c = read_byte();
			auto d = read_byte();

			return (int32_t)c + ((int32_t)d << 8);
		}

		case 0x81: {
			auto c = read_byte();
			auto d = read_byte();
			auto e = read_byte();
			auto f = read_byte();

			return (int32_t)c + ((int32_t)d << 8) + ((int32_t)e << 16) + ((int32_t)f << 24);
		}

		default:
			return (int32_t)b;
	}
}

template<> 
uint32_t reader::read() {
	auto n = (uint32_t)read_byte();

	if ((n & (1 << 7)) != 0) 
		n += (((uint32_t)read_byte()) << 7) - (1 << 7);

	if ((n & (1 << 14)) != 0) 
		n += (((uint32_t)read_byte()) << 14) - (1 << 14);

	if ((n & (1 << 21)) != 0) 
		n += (((uint32_t)read_byte()) << 14) - (1 << 14);	

	if ((n & (1 << 28)) != 0) 
		n += 0x0F << 24;

	return n;
}

template<> 
bool reader::read() {
	auto b = read_byte();
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
std::string reader::read() {
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

template<> 
unsigned char reader::read() {
	return read_byte();
}

template<>
gun reader::read() {
	auto n = read<int32_t>();
	if (n < (int32_t)gun::FIST || n > (int32_t)gun::PISTOL)
		throw read_error(false);

	return (gun)n;
}

template<>
model reader::read() {
	auto n = read<int32_t>();
	if (n < (int32_t)model::MR_FIXIT || n > (int32_t)model::CANNON)
		throw read_error(false);

	return (model)n;
}

template<>
gamemode reader::read() {
	auto n = read<int32_t>();
	if (n < (int32_t)gamemode::FFA || n > (int32_t)gamemode::EFFICIENCY_COLLECT)
		throw read_error(false);

	return (gamemode)n;
}

template<>
armor reader::read() {
	auto n = read<int32_t>();
	if (n < (int32_t)armor::BLUE || n > (int32_t)armor::YELLOW)
		throw read_error(false);

	return (armor)n;
}

template<>
shot reader::read() {
	auto read_vector = [this](float div) -> vector {
		return vector(
			(float)read<int32_t>() / div,
			(float)read<int32_t>() / div,
			(float)read<int32_t>() / div
		);
	};

	shot shot;
	shot.id = read<int32_t>();
	shot.gun = read<gun>();
	shot.from = read_vector(DMF);
	shot.to = read_vector(DMF);

	auto hit_count = read<int32_t>();
	for (int i = 0; i < hit_count; i++) {
		hit hit;
		hit.target = read<int32_t>();
		hit.life_sequence = read<int32_t>();
		hit.distance = (float)read<int32_t>() / DMF;
		hit.rays = read<int32_t>();
		hit.direction = read_vector(DNF);

		shot.hits.push_back(hit);
	}

	return shot;
}

}