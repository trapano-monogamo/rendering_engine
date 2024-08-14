#pragma once

#include "core/transform.hpp"
#include "ecs/ecs.hpp"

#include "core/mesh.hpp"
#include "core/material.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"

#include <string>

class Renderable : public Component {
public:
	std::string mesh_key;
	std::string material_key;
	std::string shader_key;
	std::string texture_key;

public:
	Renderable();
	Renderable(std::string mesh_key, std::string material_key, std::string shader_key, std::string texture_key);
	~Renderable() = default;

	void draw(Transform* t);
};

struct RenderableConfig {
	ResourceConfig<Mesh> mesh;
	ResourceConfig<Material> material;
	ResourceConfig<Shader> shader;
	ResourceConfig<Texture> texture;
};
