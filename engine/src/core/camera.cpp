#include "core/camera.hpp"
#include "math/vec.hpp"
#include <cmath>

Camera::Camera(vec3 p)
	: up(VEC3_Y), right(VEC3_X), dir(-VEC3_Z), pos(p), pitch(0.0), yaw(0.0)
{}

Camera Camera::with_ortho(float n, float f, float l, float r, float t, float b) {
	this->projection = mat4::ortho(n, f, l, r, t, b);
	return *this;
}

Camera Camera::with_perpsective(float fovy, float ar, float n, float f) {
	this->projection = mat4::perspective(fovy, ar, n, f);
	return *this;
}

void Camera::set_position(vec3 _pos) {
	this->pos = _pos;
}

void Camera::translate(vec3 t) {
	this->pos += t;
}

void Camera::rotate(float pitch, float yaw) {
	this->up.normalize();
	this->right.normalize();
	this->dir.normalize();

	float d = vec3::dot(VEC3_Y, this->up);
	vec3 vertical_axis = VEC3_Y * ((d >= 0.0) ? 1.0 : -1.0);
	
	this->up.rotate(vertical_axis, yaw);
	this->right.rotate(vertical_axis, yaw);
	this->dir.rotate(vertical_axis, yaw);

	this->up.rotate(this->right, pitch);
	this->dir.rotate(this->right, pitch);

	// this->yaw += yaw;
	// this->pitch += pitch;

	// float a = deg_to_rad(89.0);
	// if (this->pitch > a) {
	// 	this->up.rotate(this->right, a - this->pitch + pitch);
	// 	this->dir.rotate(this->right, a - this->pitch + pitch);
	// 	this->pitch = a;
	// } else if (this->pitch < -a) {
	// 	this->up.rotate(this->right, a - this->pitch + pitch);
	// 	this->dir.rotate(this->right, a - this->pitch + pitch);
	// 	this->pitch = -a;
	// } else {
	// 	this->up.rotate(this->right, pitch);
	// 	this->dir.rotate(this->right, pitch);
	// }
}
