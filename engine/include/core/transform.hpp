#pragma once

#include "ecs/ecs.hpp"
#include "math/vec.hpp"

struct Transform : public Component {
	vec3 position;
	vec3 scale;
	vec3 euler_rotations;

	Transform();
	Transform(Transform& t) = default;
	Transform(vec3 position, vec3 scale, vec3 euler_angles);

	void translate(vec3 translation);
	void rotate(vec3 axis, float angle);
	void rotate_euler(vec3 euler_angles);
	void resize(vec3 scale);
};
