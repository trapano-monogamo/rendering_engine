#include "core/renderable.hpp"
#include "ecs/ecs.hpp"

#include "utils.hpp"
#include <iostream>

Renderable::Renderable()
	: Component()
	// !!!  NOT INITIALIZING THESE HERE MAKES THEM DEFAULT INITIALIZED, SO NOT VALID WHEN YOU TRY TO RE-INITIALIZE THEM  !!!
	, va(VertexArray())
	, program(Shader())
{}

Renderable::~Renderable() {}

void Renderable::default_cube() {
	float vertices[] = {
		-0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  0.0, 0.0,
		 0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  1.0, 0.0,
		 0.5,  0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 1.0,
		-0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  0.0, 1.0,
		-0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  1.0, 1.0,
		 0.5, -0.5,  0.5,  0.0, 0.0, 1.0,  0.0, 1.0,
		 0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  0.0, 0.0,
		-0.5,  0.5,  0.5,  0.0, 1.0, 0.0,  1.0, 0.0,
	};
	unsigned int indices[] = {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1,
	};

	// this->va = VertexArray();
	va.write_buffers(vertices, sizeof(vertices), indices, sizeof(indices));
	va.enable_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	va.enable_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	va.enable_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// ~ here ~
	this->program.load_source_files("/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/vertex.shader", "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/fragment.shader");
	this->texture = Texture("/home/chiara/dev/cpp/rendering_engine/engine/assets/textures/container.jpg");
}
