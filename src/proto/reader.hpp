#ifndef PROTO_READER_HPP
#define PROTO_READER_HPP
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <string>

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
	reader(span<unsigned char> data);

	bool ends() const;

	size_t get_offset() const;

	span<unsigned char> span_from(size_t start, size_t end) const;

	unsigned char read_byte();
	
	template<typename T> 
	T read();

private:
	span<unsigned char> data;
	size_t offset;
};

}
#endif