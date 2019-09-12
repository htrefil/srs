#include <stdexcept>
#include <string>
#include <cstring>
#include <iostream>

#include "writer.hpp"
#include "strings.hpp"

namespace proto {

writer::writer() : data(nullptr), size(0), capacity(0) {}

writer::writer(writer&& other) : data(other.data), size(other.size), capacity(other.capacity) {
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

writer::~writer() {
	delete[] data;
}

ENetPacket* writer::to_packet() {
	assert(size != 0);

	auto packet = enet_packet_create(data, size, ENET_PACKET_FLAG_NO_ALLOCATE | ENET_PACKET_FLAG_RELIABLE);
	if (packet == nullptr)
		throw std::runtime_error("Failed to create packet");

	packet->freeCallback = [](ENetPacket* packet) {
		delete[] (unsigned char*)packet->data;
	};

	data = nullptr;
	size = 0;
	capacity = 0;

	return packet;
}

bool writer::is_empty() const {
	return data != nullptr;
}

span<unsigned char> writer::get_data() const {
	return span(data, size);
}

void writer::write(unsigned char b) {
	write(span(&b, 1));
}

void writer::write(bool b) {
	write_byte(b ? 1 : 0);
}

void writer::write(span<unsigned char> span) {
	if (span.get_length() > capacity) {
		auto new_data = new unsigned char[size + span.get_length() + GROW];

		memcpy(new_data, data, size);
		memcpy(new_data + size, span.get_data(), span.get_length());

		delete[] data;
		data = new_data;

		size += span.get_length();
		capacity = GROW;
	} else {
		memcpy(data + size, span.get_data(), span.get_length());		

		size += span.get_length();
		capacity -= span.get_length();
	}
}

void writer::write(int32_t n) {
	if (n >= -0x80 && n <= 0x7F)  {
		write_byte((unsigned char)n);
	} else if (n >= -0x7FFF && n <= 0x7FFF) {
		write_byte(0x80);
		write_byte((unsigned char)n);
		write_byte((unsigned char)(n >> 8));
	} else {
		write_byte(0x81);
		write_byte((unsigned char)n);
		write_byte((unsigned char)(n >> 8));
		write_byte((unsigned char)(n >> 16));
		write_byte((unsigned char)(n >> 28));
	}
}

void writer::write(uint32_t n) {
	if (n < 1 << 7) {
		write_byte((unsigned char)n);
	} else if (n < 1 << 14) {
		write_byte(((unsigned char)n & 0x7F) | 0x80);
		write_byte((unsigned char)(n >> 7));
	} else if (n < 1 << 21) {
	    write_byte(((unsigned char)n & 0x7F) | 0x80);
	    write_byte(((unsigned char)(n >> 7) & 0x7F) | 0x80);
	    write_byte((unsigned char)(n >> 14));
	} else {
		write_byte(((unsigned char)n & 0x7F) | 0x80);
		write_byte(((unsigned char)(n >> 7) & 0x7F) | 0x80);
		write_byte(((unsigned char)(n >> 14) & 0x7F) | 0x80);
		write_byte((unsigned char)(n >> 21));
	}
}

void writer::write(const char* str) {
	auto length = strlen(str) + 1;
	
	for (size_t i = 0; i < length; ) {
		rune_t rune;
		auto s = utf8_decode(&str[i], length - i, &rune);

		assert(s != 0);

		i += s;

		auto n = encode(rune);
		if (!n)
			throw std::runtime_error("Unencodable string");

		write(*n);
	}
}

void writer::write(write_fn f) {
	f(*this);
}

void writer::write(ENetPacket* packet) {
	write(span(packet->data, packet->dataLength));

	enet_packet_destroy(packet);
}

void writer::write_byte(unsigned char b) {
	write(b);
}

void writer::write(gun g) {
	write((int32_t)g);
}

void writer::write(model m) {
	write((int32_t)m);
}

void writer::write(gamemode m) {
	write((int32_t)m);
}

void writer::write(armor a) {
	write((int32_t)a);
}

void writer::write(const writer& writer) {
	write(writer.get_data());
}

}

