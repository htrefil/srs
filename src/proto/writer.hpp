#ifndef PROTO_WRITER_HPP
#define PROTO_WRITER_HPP
#include <cstdint>
#include <vector>
#include <enet/enet.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <type_traits>

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

	template<typename T>
	void write(typename std::enable_if_t<!std::is_enum_v<T>, T> v) {
		write_basic(v);
	}

	template<typename T>
	void write(typename std::enable_if_t<std::is_enum_v<T>, T> v) {
		write_basic((std::underlying_type_t<T>)v);
	}

	inline void write() {}

private:
	static constexpr size_t GROW = 16;

	void write_basic(unsigned char e);

	void write_basic(bool b);

	void write_basic(int32_t n);

	void write_basic(uint32_t n);

	void write_basic(const char* str);

	void write_basic(write_fn f);

	void write_basic(span<unsigned char> span);

	unsigned char* data;
	size_t size;
	size_t capacity;
};

/*
template<>
void writer::write(unsigned char e);

template<>
void writer::write(int32_t e);

template<>
void writer::write(uint32_t e);

template<>
void writer::write(const char* s);

template<>
void writer::write(span<unsigned char> span);
*/
}
#endif