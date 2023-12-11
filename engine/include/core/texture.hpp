#pragma once

#include "common.hpp"

#include <vector>
#include <utility>

class Texture {
private:
	unsigned int texture;
	std::vector<std::pair<GLenum, GLint>> params;

	void set_params();

public:
	Texture() = default;
	Texture(const char* filepath);
	~Texture();

	Texture with_parameter(GLenum pname, GLint param);
	Texture load_texture(const char* filepath);
	void use();
};
