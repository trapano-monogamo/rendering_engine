#include "core/scene.hpp"
#include "core/light.hpp"
#include "core/material.hpp"
#include "core/mesh.hpp"
#include "core/renderable.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "input_handler/input_hanlder.hpp"
#include "math/mat.hpp"
#include "math/utils.hpp"
#include <iostream>

// set rendering options that require gl calls
void SceneRenderingOptions::set() {
}

void ObjectRenderingOptions::set() {
	if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (cull_face.active) {
		glEnable(GL_CULL_FACE);
		glCullFace(cull_face.order);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

Scene::Scene()
	: camera(Camera(vec3(0.0, 0.0, 0.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 100.0f))
	, input_handler(nullptr)
	, rendering_options(SceneRenderingOptions())
	, background_color(vec3(0.f,0.f,0.f))
{}

void Scene::render() {
	// set rendering options
	this->rendering_options.set();

	ObjectRenderingOptions default_opts{};

	// clear screen
	glEnable(GL_DEPTH_TEST);
	glClearColor(background_color.x, background_color.y, background_color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);

	mat4 projection;
	mat4 view;
	mat4 transform;
	
	// LIGHT SOURCE
	// TODO: implement multiple source lighting
	unsigned int light_id = this->query_entities()
		.with_component<Light>(this)
		.results[0];
	Light* light = get_component<Light>(light_id);

	// query renderable components
	auto query = this->query_entities()
			.with_component<Renderable>(this)
			.results;

	for (auto& entity : query) {
		// RENDERING COMPONENTS
		Renderable* obj = this->get_component<Renderable>(entity);
		Transform* t = this->get_component<Transform>(entity);
		ObjectRenderingOptions* opts = this->get_component<ObjectRenderingOptions>(entity);

		if (opts != nullptr) {
			opts->set();
		} else {
			default_opts.set();
		}

		// emh... kind of bad to hide this statement from the user.
		// find a way to sync the transform with other position-having components like lights
		if (entity == light_id) { light->pos = t->position; }

		// TRANSFORM, VIEW, PROJECTION
		if (t != nullptr) {
			transform = mat4::transform(t->scale, t->euler_rotations, t->position);
			view = mat4::lookat(this->camera.pos, this->camera.up, this->camera.right, this->camera.dir);
			projection = this->camera.projection;
		} else {
			transform = mat4::identity();
			view = mat4::identity();
			projection = mat4::identity();
		}

		// MESH and SHADER are necessary for rendering
		auto mesh = get_resource<Mesh>(obj->mesh_key);
		auto shader = get_resource<Shader>(obj->shader_key);

		shader->set_uniform_matrix_4fv("transform", transform.m);
		shader->set_uniform_matrix_4fv("view", view.m);
		shader->set_uniform_matrix_4fv("projection", this->camera.projection.m);

		// check if MATERIAL is present
		if (!obj->material_key.empty()) {
			auto material = get_resource<Material>(obj->material_key);
			// std::cout << "id: " << entity << "\tmat key: " << obj->material_key << "\tptr: " << material.get() << std::endl;
			shader->set_uniform("material.ambient", material->ambient, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("material.diffuse", material->diffuse, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("material.specular", material->specular, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("material.shininess", material->shininess, Shader::UniformType::FLOAT, 1);
			shader->set_uniform("light.pos", light->pos, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("light.ambient", light->ambient, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("light.diffuse", light->diffuse, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("light.specular", light->specular, Shader::UniformType::FLOAT_3, 1);
			shader->set_uniform("view_pos", camera.pos, Shader::UniformType::FLOAT_3, 1);
		}

		shader->apply_uniforms();

		// check if TEXTURE is present
		if (!obj->texture_key.empty()) {
			auto texture = get_resource<Texture>(obj->texture_key);
			texture->use();
		}

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
