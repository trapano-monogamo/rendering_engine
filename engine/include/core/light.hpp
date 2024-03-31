#pragma once

#include "ecs/ecs.hpp"
#include "math/vec.hpp"

struct Light : public Component {
	vec3 pos;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	Light(vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular);
	~Light() = default;
};
