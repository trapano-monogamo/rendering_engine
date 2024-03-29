#pragma once

#include "core/transform.hpp"
#include "ecs/ecs.hpp"
#include "resource_manager/resource_manager.hpp"
#include <functional>
#include <string>

class Renderable : public Component {
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
