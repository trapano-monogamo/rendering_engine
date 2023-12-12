#pragma once

#include "math/vec.hpp"
#include "math/mat.hpp"

class Camera {
public: // should not be all public...
	mat4 projection;
	vec3 up, right, dir;
	vec3 pos;
	float pitch, yaw;

	Camera() = default;
	Camera(vec3 position);
	~Camera() = default;

	Camera with_perpsective(float fovy, float aspect_ratio, float near, float far);
	Camera with_ortho(float near, float far, float left, float right, float top, float bottom);

	void set_position(vec3 position);
	void translate(vec3 translation);
	void set_rotation(float pitch, float yaw);
	void rotate(float pitch, float yaw);
};
