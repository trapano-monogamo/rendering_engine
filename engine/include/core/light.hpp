#pragma once

#include "ecs/ecs.hpp"
#include "math/vec.hpp"

struct Light : public Component {
	vec3 pos;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	vec3 color;

	Light() = default;
	Light(Light&) = default;
	Light(const Light&) = default;
	Light(vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, vec3 color = vec3(1.0f,1.0f,1.0f));
	~Light() = default;
};
