#pragma once

#include "common.hpp"
#include "math/vec.hpp"
#include "resource_manager/resource_manager.hpp"
#include <string>
#include <vector>

struct Vertex {
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 tex_coords;

	Vertex();
	Vertex(const Vertex&) = default;
	Vertex(vec3 pos, vec3 norm, vec3 col, vec2 tex);
};

class Mesh : public Resource {
public:
	unsigned int vao, vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh();
	~Mesh();

	void load_from_file(const std::string& path) override;
	void write_buffers();
	void use();

private:
	bool has_been_built = false;
	void enable_attribute(int index, int size, GLenum type, int stride, void* ptr);
};
