#pragma once
#include "common_opengl.hpp"

namespace eng
{


class VertexArray
{
public:
	 unsigned int vao;
	 unsigned int vbo;
	 unsigned int ebo;

public:
	 unsigned int vert_count;

	 VertexArray() = default;
	 VertexArray(size_t raw_vertices_size, float* vertices, size_t raw_indices_size, unsigned int* indices);
	 ~VertexArray(); // TODO (glDeleteBuffers)
	 void use();
};


}
