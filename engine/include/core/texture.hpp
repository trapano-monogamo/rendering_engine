#pragma once

#include "common.hpp"
#include "resource_manager/manager.hpp"

#include <vector>

class Texture : public Resource {
private:
	unsigned int texture;
	std::vector<std::pair<GLenum, GLint>> params;

	// void set_params();

public:
	Texture() = default;
	Texture(const char* filepath);
	~Texture();

	void with_parameter(GLenum pname, GLint param);
	Texture load_texture(const char* filepath);
	void use();

	void load_from_file(std::string& path) override;
};
