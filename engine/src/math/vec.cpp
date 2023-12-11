#include "math/vec.hpp"
#include <cmath>

vec3::vec3(float x1, float x2, float x3) : x(x1), y(x2), z(x3) {}

float vec3::magnitude() {
	return std::sqrt(vec3::dot(*this, *this));
}

void vec3::normalize() {
	*this *= (1 / this->magnitude());
}

vec3 vec3::normalize(vec3 a) {
	a.normalize();
	return a;
}

float vec3::angle(vec3 a, vec3 b) {
	return std::acos(vec3::dot(a,b) / (a.magnitude() * b.magnitude()));
}


vec3 operator+(vec3 a, vec3 b) {
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}
vec3 operator*(vec3 a, float x) {
	return vec3(a.x * x, a.y * x, a.z * x);
}
vec3 operator-(vec3 a) {
	return vec3(a.x * -1.f, a.y * -1.f, a.z * -1.f);
}


void vec3::operator+=(vec3 a) {
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;
}
void vec3::operator*=(float x) {
	this->x *= x;
	this->y *= x;
	this->z *= x;
}


float vec3::dot(vec3 a, vec3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
