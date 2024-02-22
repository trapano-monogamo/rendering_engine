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

	// void (*load_uniforms)(Renderable&,ResourceManager&);
	std::function<void(Renderable&,ResourceManager&)> load_uniforms{ };

public:
	Renderable();
	Renderable(std::string mesh_key, std::string light_prop_key, std::string shader_key, std::string texture_key);
	~Renderable() = default;

	// void default_cube();
	// void default_sphere(int layers, int slices);
	// void default_circle(int slices);

	void draw(Transform* t);
};
