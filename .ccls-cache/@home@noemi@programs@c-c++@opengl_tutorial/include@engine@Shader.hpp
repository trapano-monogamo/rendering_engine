#pragma once
#include "common_opengl.hpp"

namespace eng
{


class Shader {
public:
	 unsigned int program;

	 Shader() = default;
	 Shader(const char* vertex_shader_filepat, const char* fragment_shader_filepath);
	 ~Shader();

	 void load_source_string(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
	 void use();

	 void set_uniform_4f(const char* uniform_name, float x, float y, float z, float w);
	 void set_uniform_matrix_4fv(const char* uniform_name, glm::mat4 m);
	 void set_uniform_1f(const char* uniform_name, float n); // opengl bug (glUniform1f, glUniform1fv do not work)
};


}
