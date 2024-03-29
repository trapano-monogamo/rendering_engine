#include "core/scene.hpp"
#include "core/mesh.hpp"
#include "core/renderable.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "input_handler/input_hanlder.hpp"
#include "math/mat.hpp"
#include "math/utils.hpp"
#include <iostream>

// set rendering options that require gl calls
void RenderingOptions::set() {
	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Scene::Scene()
	: camera(Camera(vec3(0.0, 0.0, 0.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 100.0f))
	, input_handler(nullptr)
{}

void Scene::render() {
	// set rendering options
	this->rendering_options.set();

	// clear screen
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 projection;
	mat4 view;
	mat4 transform;
	// mat4 view = mat4::lookat(this->camera.pos, this->camera.up, this->camera.right, this->camera.dir);

	// query renderable components
	auto query = this->query_entities()
			.with_component<Renderable>(this)
			.results;

	for (auto& entity : query) {
		Renderable* obj = this->get_component<Renderable>(entity);
		Transform* t = this->get_component<Transform>(entity);

		if (t != nullptr) {
			transform = mat4::transform(t->scale, t->euler_rotations, t->position);
			view = mat4::lookat(this->camera.pos, this->camera.up, this->camera.right, this->camera.dir);
			projection = this->camera.projection;
		} else {
			transform = mat4::identity();
			view = mat4::identity();
			projection = mat4::identity();
		}

		// mesh and shader are mandatory for rendering
		auto mesh = get_resource<Mesh>(obj->mesh_key);
		auto shader = get_resource<Shader>(obj->shader_key);

		shader->apply_uniforms();

		// transform/view/projection matrices are mandatory for rendering
		shader->set_uniform_matrix_4fv("transform", transform.m);
		shader->set_uniform_matrix_4fv("view", view.m);
		shader->set_uniform_matrix_4fv("projection", this->camera.projection.m);

		// check if texture is present
		if (!obj->texture_key.empty()) {
			auto texture = get_resource<Texture>(obj->texture_key);
			texture->use();
		}
		// ~ Mesh and Shader are mandatory for rendering ~
		mesh->use();
		shader->use();
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

void Scene::update() {
	// bad naming, but hey...
	this->ECS::update();
	this->input_handler.update();
}

void Scene::bind_window(GLFWwindow* window) {
	input_handler.bind_window(window);
}
