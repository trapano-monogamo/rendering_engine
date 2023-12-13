#pragma once

#include "core/vertex_array.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "ecs/ecs.hpp"
#include <cmath>

class Renderable : public Component {
public:
	VertexArray va;
	Shader program;
	Texture texture;

	// struct {
	// 	char* vertex_filepath, fragment_filepath, texture_filepath;
	// }Config;

public:
	Renderable();
	~Renderable();

	void default_cube(); // builds hard-coded VA, shader and texture

	Renderable load_shaders(const char* vertex_filepath, const char* fragment_filepath);
	Renderable load_texture(const char* filepath);
	Renderable load_va(VertexArray& va);
	// Renderable load_obj(const char* filepath);
	Renderable build();
};
