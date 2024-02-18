#include "math/vec.hpp"
#include <cmath>
#include <stdexcept>



// ..:: vec3 ::..

vec3::vec3() : x(0.0), y(0.0), z(0.0) {}

vec3::vec3(float x1, float x2, float x3) : x(x1), y(x2), z(x3) {}

vec3::vec3(std::array<float, 3> _v) {
	for (int i = 0; i < 3; i++) this->v[i] = _v[i];
}

float& vec3::operator[](int i) {
	return this->v[i];
}

float vec3::magnitude() {
	return std::sqrt(vec3::dot(*this, *this));
}

float vec3::distance(vec3 a, vec3 b) {
	return (a + -b).magnitude();
}

void vec3::normalize() {
	float mag = this->magnitude();
	if (mag == 0.0) throw std::runtime_error("division by zero");
	*this *= (1 / mag);
}

vec3 vec3::normalize(vec3 a) {
	a.normalize();
	return a;
}

float vec3::angle(vec3 a, vec3 b) {
	return std::acos(vec3::dot(a,b) / (a.magnitude() * b.magnitude()));
}

void vec3::rotate(vec3 u, float a) {
	u.normalize();
	float c = std::cos(a);
	float s = std::sin(a);
	float x = u.x;
	float y = u.y;
	float z = u.z;
	vec3 res = vec3(
		this->x * (c + x*x * (1-c))  +  this->y * (x*y * (1-c) - z*s)  +  this->z * (x*z * (1-c) + y*s),
		this->x * (y*x * (1-c) + z*s)  +  this->y * (c + y*y * (1-c))  +  this->z * (y*z * (1-c) - x*s),
		this->x * (z*x * (1-c) - y*s)  +  this->y * (z*y * (1-c) + x*s)  +  this->z * (c + z*z * (1-c))
	);
	*this = res;
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



// ..:: vec4 ::..

vec4::vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

vec4::vec4(vec3& v, float x4)
	: x(v.x), y(v.x), z(v.z), w(x4) {}

vec4::vec4(float x1, float x2, float x3, float x4)
	: x(x1), y(x2), z(x3), w(x4) {}

vec4::vec4(std::array<float, 4> _v) {
	for (int i = 0; i < 4; i++) this->v[i] = _v[i];
}

float& vec4::operator[](int i) {
	return this->v[i];
}


float vec4::magnitude() {
	return std::sqrt(vec4::dot(*this, *this));
}
void vec4::normalize() {
	*this *= (1 / this->magnitude());
}
vec4 normalize(vec4 a) {
	a.normalize();
	return a;
}

vec4 operator+(vec4 a, vec4 b) {
	return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
vec4 operator*(vec4 a, float x) {
	return vec4(a.x * x, a.y * x, a.z * x, a.w * x);
}
vec4 operator-(vec4 a) {
	return vec4(a.x * -1.f, a.y * -1.f, a.z * -1.f, a.w * -1);
}

void vec4::operator+=(vec4 a) {
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;
	this->w += a.w;
}
void vec4::operator*=(float x) {
	this->x *= x;
	this->y *= x;
	this->z *= x;
	this->w *= x;
}

float vec4::dot(vec4 a, vec4 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}
