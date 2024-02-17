#include "core/texture.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* filepath) {
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->load_texture(filepath);
}

Texture::~Texture() {
	// todo: delete texture
}

Texture Texture::load_texture(const char* filepath) {
	int width, height, nr_channels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nr_channels, 0);
	if (data) {
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture..." << std::endl;
	}
	stbi_image_free(data);

	return *this;
}

// Texture Texture::with_parameter(GLenum pname, GLint param) {
// 	this->params.push_back(std::make_pair(pname, param));
// 	return *this;
// }

void Texture::with_parameter(GLenum pname, GLint param) {
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glTexParameteri(GL_TEXTURE_2D, pname, param);
}

// void Texture::set_params() {
// 	for (auto& p : this->params) {
// 		glBindTexture(GL_TEXTURE_2D, this->texture);
// 		glTexParameteri(GL_TEXTURE_2D, p.first, p.second);
// 	}
// }

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::load_from_file(std::string& path) { }
