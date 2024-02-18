#include "core/renderable.hpp"
#include "utils.hpp"

Renderable::Renderable()
	: mesh_key("default_mesh")
	, light_prop_key("default_light_prop")
	, shader_key("default_shader")
	, texture_key("")
{}

Renderable::Renderable(std::string mesh_key, std::string light_prop_key, std::string shader_key, std::string texture_key)
	: mesh_key(mesh_key)
	, light_prop_key(light_prop_key)
	, shader_key(shader_key)
	, texture_key(texture_key)
{}

/*
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


// void Renderable::default_sphere(int layers, int slices) {
// 	std::vector<float> vertices{ 0.0, 1.0, 0.0,   1.0, 1.0, 1.0 };
// 	std::vector<unsigned int> indices{ 0 };
// 
// 	float x,y,z = 0.0;
// 	float vangle = M_PI / layers;
// 	float hangle = 2 * M_PI / slices;
// 	for (int i = 1; i < layers - 1; i++) {
// 		y = std::cos(vangle * i);
// 
// 		for (int j = 0; j < slices; j++) {
// 			x = std::cos(hangle * i);
// 			z = std::sin(hangle * i);
// 
// 			vertices.push_back(x);
// 			vertices.push_back(y);
// 			vertices.push_back(z);
// 			vertices.push_back(0.0);
// 			vertices.push_back(0.0);
// 			vertices.push_back(0.0);
// 
// 			// wtf should this be???
// 			indices.push_back(i);
// 		}
// 	}
// 
// 	vertices.push_back(0.0);
// 	vertices.push_back(-1.0);
// 	vertices.push_back(0.0);
// 	vertices.push_back(0.0);
// 	vertices.push_back(0.0);
// 	vertices.push_back(0.0);
// 
// 	indices.push_back(indices.size());
// 
// 	va.write_buffers(vertices.data(), vertices.size() * sizeof(float), indices.data(), indices.size() * sizeof(unsigned int));
// 	va.enable_attribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
// 	va.enable_attribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
// 
// 	this->program.load_source_files("/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/vertex.shader", "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/fragment.shader");
// }

void Renderable::default_circle(int N) {
	std::vector<float> vertices = { 0.f,0.f,0.f, 1.f,1.f,1.f }; // center of the cirlce (0,0,0, white)
	std::vector<unsigned int> indices{ };

	float dphi = 2*M_PI / N;
	int knext = 0;

	for (int k=1; k<=N; k++) {
		vertices.push_back(cos(k*dphi));
		vertices.push_back(sin(k*dphi));
		vertices.push_back(0.f);

		vertices.push_back(1 + .5*sin(k*dphi));
		vertices.push_back(1 + .5*cos(k*dphi));
		vertices.push_back(1 + .5*sin(2.*k*dphi));

		knext = (k+1 > N) ? 1 : k+1;

		indices.push_back(0);
		indices.push_back(k);
		indices.push_back(knext);
	}

	// this->va = VertexArray();
	va.write_buffers(vertices.data(), 6 * N * sizeof(float), indices.data(), 3 * N * sizeof(unsigned int));
	va.enable_attribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	va.enable_attribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// ~ here ~
	this->program.load_source_files("/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/circle_vertex.shader", "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/circle_fragment.shader");
}
*/
