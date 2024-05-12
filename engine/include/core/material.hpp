#pragma once

#include "math/vec.hpp"
#include "resource_manager/resource_manager.hpp"
#include <string>

class Material : public Resource {
public:
	float shininess;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	Material() = default;
	Material(float,vec3,vec3,vec3);
	~Material() = default;
	void load_from_file(const std::string& path) override;
};
