#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <ostream>

class vector {
public:
	vector();

	vector(float yaw, float pitch);

	vector(float x, float y, float z);

	float distance(const vector& other) const;

	float& operator[](size_t idx);

	float operator[](size_t idx) const;

	float x;
	float y;
	float z;
};

std::ostream& operator<<(std::ostream& stream, const vector& vector);

#endif