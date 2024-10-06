#include "core/game_app.hpp"
#include "core/camera.hpp"
#include "core/game_object.hpp"

#include "math/mat.hpp"

#include <cmath>
#include <cstdarg>

using namespace std;

class DynamicSystems : public GameApp {
private:
	float t = 0.f;
	float omega0 = 1.f;
	float gamma = .05f;

	Vector<2> initial_condition = Vector<2>({0,1});

	std::shared_ptr<GameObject> point;
	std::shared_ptr<GameObject> approx;

	static Matrix<2,2> damped_oscillator_solution(float t, float omega0, float gamma) {
		float omega = sqrt(omega0*omega0 - gamma*gamma);
		return (1 / omega0) * std::exp(-gamma * t) * Matrix<2,2>({
				gamma * sin(omega * t) + omega * cos(omega * t), sin(omega * t),
				omega0 * omega0 * sin(omega * t), -gamma * sin(omega * t) + omega * cos(omega * t)
			});
	}

	static Vector<2> damped_oscillator_field(Vector<2> p, float dt, float omega0, float gamma) {
		Vector<2> dp = (Matrix<2,2>({
			0, 1,
			-omega0*omega0, -gamma
		}) * p);

		Vector<2> res = (p + (dt * dp));

		return res;
	}

public:
	DynamicSystems(const char* title, int w, int h) : GameApp(title,w,h) {}
	~DynamicSystems() = default;

	void on_create() override {
		scene.camera = Camera(vec3(0.0, 0.0, 1.0)).with_ortho(0.1, 2.0, -1.0, 1.0, 1.0, -1.0);
		scene.input_handler = InputHandler(this->window);
		scene.background_color = vec3(0.10f, 0.10f, 0.10f);

		point = GameObjectBuilder(&scene)
			.with_renderable(RenderableConfig{
					.mesh = ResourceConfig<Mesh>("rect", "./demo/assets/meshes/square.mesh"),
					.material = ResourceConfig<Material>(),
					.shader = ResourceConfig<Shader>("shader", "./demo/assets/shaders/basic.shader"),
					.texture = ResourceConfig<Texture>(),
					})
			.with_transform(Transform {vec3(), vec3(.02,.02,.02), vec3()})
			.build();

		approx = GameObjectBuilder(&scene)
			.with_renderable(RenderableConfig{
					.mesh = ResourceConfig<Mesh>("rect"),
					.material = ResourceConfig<Material>(),
					.shader = ResourceConfig<Shader>("shader"),
					.texture = ResourceConfig<Texture>(),
					})
			.with_transform(Transform {vec3(), vec3(.02,.02,.02), vec3()})
			.build();

		point->get_mesh()->set_color(vec3(1,1,1));
	}

	void on_update(float dt) override {
		scene.update();

		t += dt;

		vec2 new_pos;

		new_pos = vec2(damped_oscillator_solution(t, omega0, gamma) * initial_condition);
		point->get_component<Transform>()->position = vec3(new_pos.x,new_pos.y,0);

		// new_pos = vec2(damped_oscillator_field(approx->get_transform()->position, dt, omega0, gamma));

		if (scene.input_handler.is_key_pressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);

		scene.render();
	}
};

int main() {
	DynamicSystems app = DynamicSystems("PP", 1500,1500);
	app.run();

	return 0;
}
