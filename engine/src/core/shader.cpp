#include "common.hpp"
#include "core/shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const char *vertex_shader_filepath, const char *fragment_shader_filepath) {
	std::ifstream f1(vertex_shader_filepath); 
	std::string vertex_shader_src = (std::stringstream() << f1.rdbuf()).str();

	std::ifstream f2(fragment_shader_filepath); 
	std::string fragment_shader_src = (std::stringstream() << f2.rdbuf()).str();

	this->load_source_string(vertex_shader_src.c_str(), fragment_shader_src.c_str());
}

Shader::~Shader() {
	glDeleteProgram(this->program);
}

void Shader::load_source_string(const char* vertex_shader_src, const char* fragment_shader_src) {
	int success;
	char infolog[512];

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, nullptr, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED: " << infolog << std::endl;
	}

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, nullptr, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: " << infolog << std::endl;
	}

	this->program = (unsigned int)glCreateProgram();
	glAttachShader(this->program, vertex_shader);
	glAttachShader(this->program, fragment_shader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->program, 512, nullptr, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED: " << infolog << std::endl;
	}

	glValidateProgram(this->program);
	glGetProgramiv(this->program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->program, 512, nullptr, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::VALIDATION_FAILED: " << infolog << std::endl;
	}

	glDetachShader(this->program, vertex_shader);
	glDeleteShader(vertex_shader);
	glDetachShader(this->program, fragment_shader);
	glDeleteShader(fragment_shader);
}

void Shader::use() {
	glUseProgram(this->program);
}

void Shader::set_uniform_1f(const char* uniform_name, float n) {
	int uniform_location = glGetUniformLocation(this->program, uniform_name);
	glUseProgram(this->program);
	glUniform1fv(uniform_location, 1, &n);
}

void Shader::set_uniform_2f(const char* uniform_name, float x, float y) {
	int uniform_location = glGetUniformLocation(this->program, uniform_name);
	glUseProgram(this->program);
	glUniform2f(uniform_location, x, y);
}

void Shader::set_uniform_3f(const char* uniform_name, float x, float y, float z) {
	int uniform_location = glGetUniformLocation(this->program, uniform_name);
	glUseProgram(this->program);
	glUniform3f(uniform_location, x, y, z);
}

void Shader::set_uniform_4f(const char* uniform_name, float x, float y, float z, float w) {
	int uniform_location = glGetUniformLocation(this->program, uniform_name);
	glUseProgram(this->program);
	glUniform4f(uniform_location, x, y, z, w);
}

void Shader::set_uniform_matrix_4fv(const char* uniform_name, float m[16]) {
	int uniform_location = glGetUniformLocation(this->program, uniform_name);
	glUseProgram(this->program);
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, m);
}
