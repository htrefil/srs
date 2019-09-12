#include <cmath>
#include <cassert>

#include "vector.hpp"

vector::vector() : x(0.0), y(0.0), z(0.0) {}

vector::vector(float yaw, float pitch) : x(-sinf(yaw) * cosf(pitch)), y(cosf(pitch)), z(cosf(pitch)) {}

vector::vector(float x, float y, float z) : x(x), y(y), z(z) {}

float vector::distance(const vector& other) const {
	auto cx = x - other.x;
	auto cy = y - other.y;
	auto cz = z - other.z;

	return sqrtf(cx * cx + cy * cy + cz * cz);
}

float& vector::operator[](size_t idx) {
	switch (idx) {
		case 0:
			return x;
		
		case 1:
			return y;
		
		case 2:
			return z;

		default:
			assert(false);
	}
}

float vector::operator[](size_t idx) const {
	switch (idx) {
		case 0:
			return x;
		
		case 1:
			return y;
		
		case 2:
			return z;

		default:
			assert(false);
	}
}

std::ostream& operator<<(std::ostream& stream, const vector& vector) {
	return stream << "X: " << vector.x << ", Y: "<< vector.y << ", Z: " << vector.z;
}
