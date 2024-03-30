#pragma once

#include "common.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>

#include <memory>
#include <string>

#include "core/game_app.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/transform.hpp"
#include "core/renderable.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "input_handler/input_hanlder.hpp"
#include "math/utils.hpp"
#include "math/vec.hpp"
#include "ecs/ecs.hpp"

class GravitySim : public GameApp {
private:
	vec3 light_color = vec3(1.0f, 0.0f, 0.0f);
	float speed = 2.5f;
	float t = 10.f;

	void create_circle_mesh_file(const char* filename, int N);

	struct Body : public Component {
		float mass = 1.0f;
		vec3 position = vec3();
		vec3 velocity = vec3();
		vec3 acceleration = vec3();
		vec3 force = vec3();

		Body() = default;
		Body(float m, vec3 p, vec3 v, vec3 a, vec3 f)
			: mass(m)
			, position(p)
			, velocity(v)
			, acceleration(a)
			, force(f)
		{}
	};

	class GravitySystem : public System {
	private:
		bool running = false;

	public:
		Scene* scene;
		float dt = 0.0f;
		float G = 0.3f;

		GravitySystem() : scene(nullptr), dt(0.0f) {}
		GravitySystem(GravitySystem&) = default;

		void update() override;

		void update_gravity(Scene* scene);
		void update_bodies(Scene* scene);
	};

public:
	GravitySim(const char* title, int width, int height) : GameApp(title, width, height) {}
	GravitySim(GravitySim&) = default;
	~GravitySim() { /* delete gravity_system; */ }

	void on_create() override;
	void on_update(float dt) override;
};
