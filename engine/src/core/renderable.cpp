#include "core/renderable.hpp"
#include "utils.hpp"

Renderable::Renderable()
	: Component()
	, mesh_key("default_mesh")
	, material_key("default_light_prop")
	, shader_key("default_shader")
	, texture_key("")
{}

Renderable::Renderable(std::string mesh_key, std::string material_key, std::string shader_key, std::string texture_key)
	: Component()
	, mesh_key(mesh_key)
	, material_key(material_key)
	, shader_key(shader_key)
	, texture_key(texture_key)
{}
