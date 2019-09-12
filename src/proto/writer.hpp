#ifndef PROTO_WRITER_HPP
#define PROTO_WRITER_HPP
#include <cstdint>
#include <vector>
#include <enet/enet.h>
#include <cstdlib>
#include <functional>
#include <iostream>

#include "consts.hpp"
#include "items.hpp"
#include "../span.hpp"

namespace proto {

class writer {
public:
	using write_fn = std::function<void(writer&)>;

	writer();

	writer(const writer&) = delete;

	writer(writer&& other);

	~writer();

	ENetPacket* to_packet();

	bool is_empty() const;

	span<unsigned char> get_data() const;

	template<typename T, typename... Args> 
	void write(T first, Args... args) {
		write(first);
		write(args...);
	}

	void write(unsigned char b);

	void write(bool b);

	void write(span<unsigned char> span);

	void write(int32_t n);

	void write(uint32_t n);

	void write(const char* str);

	void write(write_fn f);

	void write(ENetPacket* packet);

	void write(gun g);

	void write(model m);

	void write(gamemode m);

	void write(armor a);

	void write(const writer& writer);
	
private:
	void write_byte(unsigned char b);

	static constexpr size_t GROW = 16;

	unsigned char* data;
	size_t size;
	size_t capacity;
};

}
#endif