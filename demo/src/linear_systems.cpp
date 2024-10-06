#include "linear_systems.hpp"
#include "math/utils.hpp"

LSScene::LSScene(const char* title, int width, int height)
	: GameApp(title, width, height) { }

void LSScene::on_create() {
	scene.camera = Camera(vec3(0.0, 1.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);
	scene.input_handler = InputHandler(this->window);
	scene.background_color = vec3(0.10f, 0.10f, 0.10f);

	scene.register_resource("line", "../engine/assets/meshes/cube2.mesh");


}

void LSScene::on_update(float) { }
