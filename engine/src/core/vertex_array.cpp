#include "core/vertex_array.hpp"

VertexArray::VertexArray() {
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	glGenVertexArrays(1, &this->vao);
}

VertexArray::~VertexArray() {
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

void VertexArray::use() {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

void VertexArray::write_buffers(float* vertices, unsigned int n, unsigned int* indices, unsigned int m) {
	this->elements_count = m / sizeof(unsigned int);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, vertices, GL_STATIC_DRAW);
	if (indices != nullptr) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m, indices, GL_STATIC_DRAW);
	}
}

void VertexArray::enable_attribute(int index, int size, GLenum type, int stride, void* ptr) {
	this->use();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(index);
}
