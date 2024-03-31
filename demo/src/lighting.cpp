#include "lighting.hpp"

#include "core/game_app.hpp"
#include "core/light.hpp"
#include "core/material.hpp"
#include "core/mesh.hpp"
#include "core/transform.hpp"
#include "core/renderable.hpp"
#include "core/shader.hpp"
#include "math/utils.hpp"
#include <math.h>
#include <iostream>
#include <memory>

float f(float x, float y) {
	return sin(x + y);
}

// res should be a reference so the function can change all instances?
// maybe it doesn't make sense, so it could be like:
//   Resource* res
// and the ResourceManager::get_resource() function only does
//   R* loaded_res = new R{};
//   ... build_func(loaded_res);
void terrain_builder(std::shared_ptr<Resource> res) {
	Material material = Material();

	// int size_x = 100;
	// int size_y = 100;

	// for (int i=0; i<size_y; i++) {
	// 	for (int j=0; j<size_x; j++) {
	// 		mesh->vertices.push
	// 	}
	// }
	
	material.ambient = vec3(0.0215,0.1745,0.0215);
	material.diffuse = vec3(0.07568,0.61424,0.07568);
	material.specular = vec3(0.633,0.727811,0.633);
	material.shininess = 200;

	*res.get() = material;
}

LightingScene::LightingScene(const char* title, int width, int height)
	: GameApp(title, width, height) { }

void LightingScene::on_create() {
	// default intialize this
	scene.camera = Camera(vec3(0.0, 1.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);
	// can't this be done in GameApp directly???
	scene.input_handler = InputHandler(this->window);
	scene.background_color = vec3(0.05f, 0.05f, 0.05f);

	scene.register_resource("light_shader",     "../engine/assets/shaders/light.shader");
	scene.register_resource("source_shader",    "../engine/assets/shaders/basic2.shader");
	scene.register_resource("cube_mesh",        "../engine/assets/meshes/cube2.mesh");
	scene.register_resource("bronze_material",  "../engine/assets/materials/bronze.mat");
	scene.register_resource("emerald_material", "../engine/assets/materials/emerald.mat");



	scene.register_resource("test_resource", terrain_builder);
	std::shared_ptr<Material> material = scene.get_resource<Material>("test_resource");



	Transform* obj1_t = new Transform();
	obj1_t->translate(vec3(-1.0, 0.0, 0.0));
	auto obj1_id = this->scene.add_entity();
	scene.add_component(obj1_id, new Renderable("cube_mesh", "bronze_material", "light_shader", ""));
	scene.add_component(obj1_id, obj1_t);

	Transform* obj2_t = new Transform();
	obj2_t->translate(vec3(1.0, 0.0, 0.0));
	auto obj2_id = this->scene.add_entity();
	scene.add_component(obj2_id, new Renderable("cube_mesh", "test_resource", "light_shader", ""));
	scene.add_component(obj2_id, obj2_t);

	Transform* source_t = new Transform();
	source_t->translate(vec3(1.8f, 2.5f, -1.5f));
	source_t->resize(vec3(.5f, .5f, .5f));
	source_id = this->scene.add_entity();
	scene.add_component(source_id, new Renderable("cube_mesh", "", "source_shader", ""));
	scene.add_component(source_id, source_t);
	scene.add_component(source_id, new Light(
		source_t->position,
		vec3(0.2f, 0.2f, 0.2f),
		vec3(0.5f, 0.5f, 0.5f),
		vec3(1.0f, 1.0f, 1.0f)
	));
}

float ambient = 0.1f;
float specular_strength = 0.8f;

void LightingScene::on_update(float dt) {
	t += 0.005f;
	// light_color = vec3(.5*(1+sin(t)), .5*(1+cos(t)), .5 + sin(t)*cos(t));

	scene.get_component<Transform>(source_id)->position = vec3(sin(t), cos(t), sin(t)*cos(t)) * 2.0;

	auto source_shader = scene.get_resource<Shader>("source_shader");
	source_shader->set_uniform("light_color", light_color, Shader::UniformType::FLOAT_3, 1);

	scene.update();

	if (scene.input_handler.is_key_pressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_X))
		scene.rendering_options.wireframe = true;
	if (scene.input_handler.is_key_pressed(GLFW_KEY_F))
		scene.rendering_options.wireframe = false;

	if (scene.input_handler.is_key_pressed(GLFW_KEY_W)) {
		vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
		scene.camera.pos += (u * camera_speed * dt);
	}
	if (scene.input_handler.is_key_pressed(GLFW_KEY_S)) {
		vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
		scene.camera.pos += (-u * camera_speed * dt);
	}
	if (scene.input_handler.is_key_pressed(GLFW_KEY_A))
		scene.camera.pos += (-scene.camera.right * camera_speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_D))
		scene.camera.pos += (scene.camera.right * camera_speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_UP))
		scene.camera.rotate(camera_speed/1.8 * dt, 0.0);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_DOWN))
		scene.camera.rotate(-camera_speed/1.8 * dt, 0.0);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_LEFT))
		scene.camera.rotate(0.0, camera_speed/1.8 * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_RIGHT))
		scene.camera.rotate(0.0, -camera_speed/1.8 * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_SPACE))
		scene.camera.translate(VEC3_Y * camera_speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_LEFT_SHIFT))
		scene.camera.translate(-VEC3_Y * camera_speed * dt);

	scene.render();
}
