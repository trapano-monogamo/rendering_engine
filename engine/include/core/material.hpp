#pragma once

#include "math/vec.hpp"
#include "resource_manager/resource_manager.hpp"
#include <string>

class LightProperties : public Resource {
public:
	float shininess;
	vec3 ambient;
	vec3 diffuse;
	vec3 reflective;

	LightProperties() = default;
	LightProperties(float,vec3,vec3,vec3);
	~LightProperties() = default;
	void load_from_file(std::string& path) override;
};
