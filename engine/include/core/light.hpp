#pragma once

#include "ecs/ecs.hpp"
#include "math/vec.hpp"

struct Light : public Component {
	vec3 color;

	vec3 pos;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	Light() = default;
	Light(Light&) = default;
	Light(const Light&) = default;
	Light(vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular);
	~Light() = default;
};
