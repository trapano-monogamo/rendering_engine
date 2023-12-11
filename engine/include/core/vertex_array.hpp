#pragma once

#include "common.hpp"

class VertexArray {
private:
	unsigned int vao, vbo, ebo;

public:
	VertexArray();
	~VertexArray();

	void use();

	void write_buffers(float* vertices, unsigned int n, unsigned int* indices, unsigned int m);
	void enable_attribute(int index, int size, GLenum type, int stride, void* ptr);
};