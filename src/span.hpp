#ifndef SPAN_HPP
#define SPAN_HPP
#include <vector>
#include <cassert>
#include <cstdlib>

template<typename T>
class span {
public:
	span(const T* data, size_t length) : data(data), length(length) {}

	span(const std::vector<T>& data) : data(data.data()), length(data.size()) {}

	const T* get_data() const {
		return data;
	}

	size_t get_length() const {
		return length;
	}

	const T* cbegin() const {
		return data;
	}

	const T* cend() const {
		return data + length;
	}

	const T& operator[](size_t idx) const {
		assert(idx < length);

		return data[idx];
	}

	span<T> sub(size_t start, size_t end) const {
		assert(start <= end && end >= start && end <= length);

		return span(data + start, end - start);
	}

private:
	const T* data;
	size_t length;
};

#endif