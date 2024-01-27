#pragma once

#include "core/vertex_array.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/transform.hpp"
#include "ecs/ecs.hpp"

class Renderable : public Component {
public:
	VertexArray va;
	Shader program;
	Texture texture;

	// struct {
	// 	char* vertex_filepath, fragment_filepath, texture_filepath;
	// }Config;

public:
	// Renderable(std::shared_ptr<VertexArray> va, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Renderable();
	~Renderable();

	void default_cube(); // builds hard-coded VA, shader and texture
	void default_sphere(int layers, int slices);

	void load_va(VertexArray& va);
	void load_shader(Shader& program);
	void load_texture(Texture& texture);
	// Renderable load_obj(const char* filepath);
	Renderable build();

	void draw(Transform* t);
};
