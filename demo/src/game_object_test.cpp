#include "game_object_test.hpp"
#include "math/utils.hpp"

#include "core/game_object.hpp"
#include "core/light.hpp"

GOScene::GOScene(const char* title, int width, int height)
	: GameApp(title, width, height) {}

void GOScene::on_create() {
	//scene.camera = Camera(vec3(0.0, 1.0, 3.0)
	scene.camera = Camera(vec3(0.0, 1.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);
	scene.input_handler = InputHandler(this->window);
	scene.background_color = vec3(0.10f, 0.10f, 0.10f);

	GameObjectBuilder(&scene)
		.with_renderable(RenderableConfig{
						.mesh = ResourceConfig<Mesh>("my_mesh", "./demo/assets/meshes/cube2.mesh"),
						.material = ResourceConfig<Material>("my_material", "./demo/assets/materials/jade.mat"),
						.shader = ResourceConfig<Shader>("my_shader", "./demo/assets/shaders/light.shader"),
						.texture = ResourceConfig<Texture>()
					})
		.with_transform( Transform{vec3(0,0,-1), vec3(1,1,1), vec3()} )
		.build();
	
	std::shared_ptr<GameObject> go = GameObjectBuilder(&scene)
		.with_renderable(RenderableConfig{
				.mesh = ResourceConfig<Mesh>("light_mesh", "./demo/assets/meshes/cube2.mesh"),
				.material = ResourceConfig<Material>(),
				.shader = ResourceConfig<Shader>("light_shader", "./demo/assets/shaders/basic.shader"),
				.texture = ResourceConfig<Texture>(),
				})
		.with_transform( Transform{vec3(-2,2,0), vec3(1,1,1), vec3()} )
		.with_component(Light{vec3(-2,2,0), vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f)})
		.build();
	
	go->get_mesh()->set_color(vec3(0.5, 0.0, 0.5));
	go->get_component<Light>()->color = vec3(0.5, 0.0, 0.5);
}

void GOScene::on_update(float dt) {
	scene.update();

	if (scene.input_handler.is_key_pressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	// if (scene.input_handler.is_key_pressed(GLFW_KEY_X))
	// 	scene.rendering_options.wireframe = true;
	//// if (scene.input_handler.is_key_pressed(GLFW_KEY_F))
	//// 	scene.rendering_options.wireframe = false;

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
