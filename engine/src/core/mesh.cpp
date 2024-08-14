#include "core/mesh.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

Vertex::Vertex()
	: position()
	, normal()
	, color(1.f, 1.f, 1.f)
	, tex_coords()
{}

Vertex::Vertex(vec3 pos, vec3 norm, vec3 col, vec2 tex)
	: position(pos)
	, normal(norm)
	, color(col)
	, tex_coords(tex)
{}

Mesh::Mesh()
	: vertices()
	, indices()
{
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	glGenVertexArrays(1, &this->vao);
}

// Mesh::Mesh(Mesh& other)
// 	: vertices(other.vertices)
// 	, indices(other.indices)
// {
// 	glGenBuffers(1, &this->vbo);
// 	glGenBuffers(1, &this->ebo);
// 	glGenVertexArrays(1, &this->vao);
// 
// 	write_buffers();
// }

// Mesh::Mesh(const Mesh& other)
// 	: vertices(other.vertices)
// 	, indices(other.indices)
// {
// 	glGenBuffers(1, &this->vbo);
// 	glGenBuffers(1, &this->ebo);
// 	glGenVertexArrays(1, &this->vao);
// 
// 	write_buffers();
// }

Mesh::~Mesh() {
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

void Mesh::load_from_file(const std::string& path) {
	std::ifstream f(path);
	if (!f.good()) throw std::runtime_error("Could not open Mesh resource file.");

	enum VertexField {
		NONE,
		POSITION,
		NORMAL,
		COLOR,
		TEXTURE,
		INDEX,
	};

	int size = -1;
	int elements = -1;
	int i = 0;

	std::string tmp;

	bool has_color = false;

	std::string line;
	std::stringstream line_content;
	VertexField field;
	while (getline(f,line)) {
		std::stringstream().swap(line_content);
		line_content << line;

		if (line.find("#field") != std::string::npos)
		{
			i = 0;
			if (line.find("position") != std::string::npos) field = POSITION;
			else if (line.find("normal") != std::string::npos) field = NORMAL;
			else if (line.find("tex_coords") != std::string::npos) field = TEXTURE;
			else if (line.find("index") != std::string::npos) field = INDEX;
			else if (line.find("color") != std::string::npos) {
				field = COLOR;
				has_color = true;
			}
		}
		else if (line.find("#param") != std::string::npos)
		{
			if (line.find("size") != std::string::npos) {
				line_content >> tmp >> tmp >> size;
				vertices = std::vector<Vertex>(size);
			} else if (line.find("elements") != std::string::npos) {
				line_content >> tmp >> tmp >> elements;
				indices = std::vector<unsigned int>(elements);
			} else { throw std::runtime_error("Invalid argument for '#param'"); }

		}
		else if (!line.empty())
		{
			if (size == -1) { throw std::runtime_error("Missing 'size' parameter for Mesh."); }
			switch (field) {
				case POSITION:
					line_content >> vertices[i].position.x >> vertices[i].position.y >> vertices[i].position.z;
					break;
				case NORMAL:
					line_content >> vertices[i].normal.x >> vertices[i].normal.y >> vertices[i].normal.z;
					break;
				case COLOR:
					line_content >> vertices[i].color.x >> vertices[i].color.y >> vertices[i].color.z;
					break;
				case TEXTURE:
					line_content >> vertices[i].tex_coords.u >> vertices[i].tex_coords.v;
					break;
				case INDEX:
					line_content >> indices[i];
					break;
				default:
					i--; // do nothing
					break;
			}
			i++;
		}

		if (!has_color) {
			for (int i=0; i<size; i++) {
				vertices[i].color = vec3(1.0f, 1.0f, 1.0f);
			}
		}

		if (elements == -1) {
			indices.clear();
			for (int idx=0; idx<elements; idx++) indices.push_back(idx);
		}
	}

	write_buffers();
}

void Mesh::use() {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

void Mesh::write_buffers() {
	int gl_vertices_size = vertices.size() * 11;
	float* gl_vertices = new float[gl_vertices_size]; // 1 Vertex = 11 floats
	for (unsigned int i = 0; i<vertices.size(); i++) {
		gl_vertices[i * 11 + 0] = vertices[i].position.x;
		gl_vertices[i * 11 + 1] = vertices[i].position.y;
		gl_vertices[i * 11 + 2] = vertices[i].position.z;

		gl_vertices[i * 11 + 3] = vertices[i].normal.x;
		gl_vertices[i * 11 + 4] = vertices[i].normal.y;
		gl_vertices[i * 11 + 5] = vertices[i].normal.z;

		gl_vertices[i * 11 + 6] = vertices[i].color.r;
		gl_vertices[i * 11 + 7] = vertices[i].color.g;
		gl_vertices[i * 11 + 8] = vertices[i].color.b;

		gl_vertices[i * 11 + 9] = vertices[i].tex_coords.u;
		gl_vertices[i * 11 +10] = vertices[i].tex_coords.v;
	}

	// if (indices.empty()) {
	// 	for (unsigned int i=0; i<vertices.size(); i++) indices.push_back(i);
	// }

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gl_vertices_size, gl_vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

	if (!has_been_built) { // avoid reactivating everything if the vertex data is only being updated
		enable_attribute(0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
		enable_attribute(1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		enable_attribute(2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		enable_attribute(3, 2, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));
		has_been_built = true;
	}

	delete[] gl_vertices;
}

void Mesh::enable_attribute(int index, int size, GLenum type, int stride, void* ptr) {
	this->use();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, ptr);
	glEnableVertexAttribArray(index);
}


void Mesh::set_color(const std::vector<vec3>& buffer) {
	if (buffer.size() != vertices.size()) {
		std::cerr << "Provided colors and vertex buffer do not match in size." << std::endl;
		return;
	}
	for (size_t i=0; i<vertices.size(); i++) vertices[i].color = buffer[i];
	write_buffers();
}

void Mesh::set_color(const vec3& c) {
	for (size_t i=0; i<vertices.size(); i++) vertices[i].color = c;
	write_buffers();
}
