#pragma once

#include "resource_manager/resource_manager.hpp"
#include "common.hpp"

#include <cstddef>
#include <string>
#include <unordered_map>


/* this doesn't work */
#define SHADER_ASSETS_DIRECTORY "../engine/assets/shaders/"
#ifdef CUSTOM_SHADER_ASSETS_DIRECTORY
	static const char* _CUSTOM_SHADER_ASSETS_DIRECTORY = CUSTOM_SHADER_ASSETS_DIRECTORY;
#else
	static const char* _CUSTOM_SHADER_ASSETS_DIRECTORY = "";
#endif


class Shader : public Resource {
public:
	enum UniformType {
		FLOAT,
		INT,
		FLOAT_2,
		FLOAT_3,
		FLOAT_4,
		INT_2,
		INT_3,
		INT_4,
		FLOAT_ARRAY,
		INT_ARRAY,
	};

	struct Uniform {
		UniformType type;
		GLint size;
		GLvoid* data;
	};

private:
	unsigned int program = 0;
	std::unordered_map<std::string, Uniform> uniforms;

public:
	Shader();
	~Shader();

	void load_from_file(const std::string& path) override;

	void load_source_files(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
	void load_source_string(const char* vertex_shader_filepath_src, const char* fragment_shader_src);
	void use();

	void set_uniform_1f(const char* uniform_name, float x); // opengl bug (glUniform1f, glUniform1fv does not work)
	void set_uniform_2f(const char* uniform_name, float x, float y);
	void set_uniform_3f(const char* uniform_name, float x, float y, float z);
	void set_uniform_4f(const char* uniform_name, float x, float y, float z, float w);
	void set_uniform_2fv(const char* uniform_name, float v[2]);
	void set_uniform_matrix_4fv(const char* uniform_name, float m[16]);

	// TODO: T value should be a const reference or a normal reference
	template<typename T>
	void set_uniform(const std::string& name, T value, UniformType type, GLint size);

	void apply_uniforms();
};


template<typename T>
void Shader::set_uniform(const std::string &name, T value, UniformType type, GLint size) {
	auto it = uniforms.find(name);
	if (it != uniforms.end()) {
		it->second.type = type;
		it->second.size = size;
		it->second.data = new T(value);
	} else {
		Uniform ud{ type, size, new T(value) };
		uniforms.insert({name, ud});
	}
}
