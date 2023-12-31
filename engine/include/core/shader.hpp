#pragma once

class Shader {
private:
	unsigned int program;

public:
	Shader();
	// Shader(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
	~Shader();

	void load_source_files(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
	void load_source_string(const char* vertex_shader_filepath_src, const char* fragment_shader_src);
	void use();

	void set_uniform_1f(const char* uniform_name, float x); // opengl bug (glUniform1f, glUniform1fv does not work)
	void set_uniform_2f(const char* uniform_name, float x, float y);
	void set_uniform_3f(const char* uniform_name, float x, float y, float z);
	void set_uniform_4f(const char* uniform_name, float x, float y, float z, float w);
	void set_uniform_matrix_4fv(const char* uniform_name, float m[16]);
};
