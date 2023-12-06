#include "engine/VertexArray.hpp"
#include <iostream>

eng::VertexArray::VertexArray(size_t raw_vertices_size, float* vertices, size_t raw_indices_size, unsigned int* indices)
	 : vert_count(raw_indices_size / sizeof(unsigned int))
{

	 glGenVertexArrays(1, &this->vao);
	 glGenBuffers(1, &this->vbo);
	 glGenBuffers(1, &this->ebo);

	 glBindVertexArray(this->vao);

	 glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	 glBufferData(GL_ARRAY_BUFFER, raw_vertices_size, vertices, GL_STATIC_DRAW);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, raw_indices_size, indices, GL_STATIC_DRAW);

	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	 glEnableVertexAttribArray(1);
}

eng::VertexArray::~VertexArray() {}

void eng::VertexArray::use() {
	 glBindVertexArray(this->vao);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}
