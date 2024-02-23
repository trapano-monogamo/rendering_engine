#pragma once

#include "core/transform.hpp"
#include "resource_manager/manager.hpp"
#include <functional>
#include <string>

class Renderable : public Transform {
public:
	std::string mesh_key;
	std::string light_prop_key;
	std::string shader_key;
	std::string texture_key;

public:
	Renderable();
	Renderable(std::string mesh_key, std::string light_prop_key, std::string shader_key, std::string texture_key);
	~Renderable() = default;

	void draw(Transform* t);
};
