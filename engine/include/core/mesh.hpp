#pragma once

#include "common.hpp"
#include "math/vec.hpp"
#include "resource_manager/manager.hpp"
#include <string>
#include <vector>

struct Vertex {
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 tex_coords;

	Vertex();
	Vertex(Vertex& v) = default;
};

class Mesh : public Resource {
public:
	unsigned int vao, vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh();
	~Mesh();

	void load_from_file(std::string& path) override;
	void use();

private:
	void write_buffers();
	void enable_attribute(int index, int size, GLenum type, int stride, void* ptr);
};
