#include "lighting.hpp"

#include "core/game_app.hpp"
#include "core/transform.hpp"
#include "core/renderable.hpp"
#include "core/shader.hpp"
#include "math/utils.hpp"
#include <math.h>

LightingScene::LightingScene(const char* title, int width, int height)
	: GameApp(title, width, height) { }

void LightingScene::on_create() {
	scene.camera = Camera(vec3(0.0, 1.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);
	scene.input_handler = InputHandler(this->window);

	scene.register_resource("light_shader", "../engine/assets/shaders/light.shader");
	scene.register_resource("source_shader", "../engine/assets/shaders/basic2.shader");
	scene.register_resource("cube_mesh",    "../engine/assets/meshes/cube.mesh");

	auto obj_id = this->scene.add_entity();
	scene.add_component(obj_id, new Renderable("cube_mesh", "", "light_shader", ""));
	scene.add_component(obj_id, new Transform());

	Transform* source_t = new Transform();
	source_t->translate(vec3(1.8f, 2.5f, -1.5f));
	source_t->resize(vec3(.5f, .5f, .5f));
	source_id = this->scene.add_entity();
	scene.add_component(source_id, new Renderable("cube_mesh", "", "source_shader", ""));
	scene.add_component(source_id, source_t);
}

float ambient = 0.5f;

void LightingScene::on_update(float dt) {
	// t += 0.03f;
	// light_color = vec3(.5*(1+sin(t)), .5*(1+cos(t)), .5 + sin(t)*cos(t));

	auto light_t = scene.get_component<Transform>(source_id);

	auto light_shader = scene.get_resource<Shader>("light_shader");
	light_shader->set_uniform("light_color", light_color, Shader::UniformType::FLOAT_3, 1);
	light_shader->set_uniform("ambient", ambient, Shader::UniformType::FLOAT, 1);
	light_shader->set_uniform("light_pos", light_t->position, Shader::UniformType::FLOAT_3, 1);

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
