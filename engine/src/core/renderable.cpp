#include "core/renderable.hpp"
#include "utils.hpp"

Renderable::Renderable()
	: mesh_key("default_mesh")
	, light_prop_key("default_light_prop")
	, shader_key("default_shader")
	, texture_key("")
{}

Renderable::Renderable(std::string mesh_key, std::string light_prop_key, std::string shader_key, std::string texture_key)
	: mesh_key(mesh_key)
	, light_prop_key(light_prop_key)
	, shader_key(shader_key)
	, texture_key(texture_key)
{}
