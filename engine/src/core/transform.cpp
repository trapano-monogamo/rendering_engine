#include "core/transform.hpp"
#include <cmath>

Transform::Transform()
	: position(vec3())
	, scale(vec3(1.0, 1.0, 1.0))
	, euler_rotations(vec3())
{}

Transform::Transform(vec3 p, vec3 s, vec3 r)
	: position(p)
	, scale(s)
	, euler_rotations(r)
{}

void Transform::translate(vec3 t) {
	this->position += t;
}

void Transform::rotate_euler(vec3 ea) {
	this->euler_rotations += ea;
}

void Transform::resize(vec3 s) {
	this->scale.x *= s.x;
	this->scale.y *= s.y;
	this->scale.z *= s.z;
}
