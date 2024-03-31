#include "scenes.hpp"

void GravitySim::on_create() {
	scene.camera = Camera(vec3(0.0, 0.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);
	scene.input_handler = InputHandler(this->window);

	scene.register_resource("basic_shader",			"../engine/assets/shaders/basic.shader");
	scene.register_resource("basic2_shader",		"../engine/assets/shaders/basic2.shader");
	scene.register_resource("basic3_shader",		"../engine/assets/shaders/basic3.shader");
	scene.register_resource("light_shader",			"../engine/assets/shaders/light.shader");
	scene.register_resource("cube_mesh",			"../engine/assets/meshes/cube.mesh");
	scene.register_resource("square_mesh",			"../engine/assets/meshes/square.mesh");
	scene.register_resource("circle_mesh",			"../engine/assets/meshes/circle.mesh");
	scene.register_resource("container_texture",	"../engine/assets/textures/container.jpg");

	auto test_shader = scene.get_resource<Shader>("basic2_shader");
	test_shader->set_uniform<float>("t", 1.f, Shader::UniformType::FLOAT, 1);

	auto test_texture = scene.get_resource<Texture>("container_texture");
	test_texture->with_parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	test_texture->with_parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	test_texture->with_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	test_texture->with_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GravitySystem* gravity_system = new GravitySystem();
	scene.add_system(gravity_system);
	scene.get_system<GravitySystem>()->scene = &scene;

	uint32_t id = scene.add_entity();
	Renderable* floor = new Renderable("square_mesh", "", "basic3_shader", "container_texture");
	Transform* t = new Transform();
	t->translate(vec3(0.0, -5.0, 0.0));
	t->rotate_euler(vec3(PI/2,0,0));
	t->resize(vec3(10.0, 10.0, 0.0));
	// scene.add_component<Renderable>(id, floor);
	// scene.add_component<Transform>(id, t);
	
	float masses[] = {
		1.f,
		1.f,
	};

	vec3 positions[] = {
		vec3(-3.f, 0.f, -5.f),
		vec3( 3.f, 0.f, -5.f), };

	vec3 velocities[] = {
		vec3(0.0f,  1.0f, 0.0f),
		vec3(0.0f, -1.0f, 0.0f), };

	for (int i = 0; i < (int)(sizeof(positions) / sizeof(vec3)); i++) {
		// Renderable* obj = new Renderable("circle_mesh", "", "basic2_shader", "");
		Renderable* obj = new Renderable("cube_mesh", "", "basic_shader", "");
		// std::shared_ptr<Shader> shader = scene.get_resource<Shader>("light_shader");
		// shader->set_uniform("light_color", this->light_color, Shader::UniformType::FLOAT_3, 1);
		Transform* t = new Transform();
		t->translate(positions[i]);

		Body* b = new Body{ masses[i], positions[i], velocities[i], vec3(), vec3() };

		uint32_t id = scene.add_entity();
		scene.add_component<Renderable>(id, obj);
		scene.add_component<Transform>(id, t);
		scene.add_component<Body>(id, b);
	}
}

void GravitySim::on_update(float dt) {
	t+=0.1f;
	scene.get_resource<Shader>("basic_shader")
		->set_uniform("t", t, Shader::UniformType::FLOAT, 1);

	scene.get_system<GravitySystem>()->dt = dt; // ewwww


	// should Scene::render() and ECS::update() really
	// be called by the user in App::on_update()?

	scene.update();


	// GIVE THIS ABOMINATION TO AN INPUT HANDLER WITH CUSTOM KEY BINDINGS

	if (scene.input_handler.is_key_pressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_X))
		scene.rendering_options.wireframe = true;
	if (scene.input_handler.is_key_pressed(GLFW_KEY_F))
		scene.rendering_options.wireframe = false;

	if (scene.input_handler.is_key_pressed(GLFW_KEY_W)) {
		vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
		scene.camera.pos += (u * speed * dt);
	}
	if (scene.input_handler.is_key_pressed(GLFW_KEY_S)) {
		vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
		scene.camera.pos += (-u * speed * dt);
	}
	if (scene.input_handler.is_key_pressed(GLFW_KEY_A))
		scene.camera.pos += (-scene.camera.right * speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_D))
		scene.camera.pos += (scene.camera.right * speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_UP))
		scene.camera.rotate(speed/1.8 * dt, 0.0);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_DOWN))
		scene.camera.rotate(-speed/1.8 * dt, 0.0);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_LEFT))
		scene.camera.rotate(0.0, speed/1.8 * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_RIGHT))
		scene.camera.rotate(0.0, -speed/1.8 * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_SPACE))
		scene.camera.translate(VEC3_Y * speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_LEFT_SHIFT))
		scene.camera.translate(-VEC3_Y * speed * dt);

	scene.render();
}

void GravitySim::create_circle_mesh_file(const char* filename, int N) {
	std::ofstream f(filename);
	if (!f.good()) return;

	f << "#param size " << N + 1 << std::endl;
	f << "#param elements " << 3 * N << std::endl;

	float dphi = 2*M_PI / N;
	int knext = 0;

	f << "#field position" << std::endl;
	f << "0.0 0.0 0.0" << std::endl;
	for (int k=1; k<=N; k++) // positions
		f << cos(k*dphi) << " " << sin(k*dphi) << " " << 0.f << std::endl;

	f << "#field normal" << std::endl;
	f << "0.0 0.0 0.0" << std::endl;
	for (int k=1; k<=N; k++) // normals
		f << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;

	f << "#field color" << std::endl;
	f << "0.0 0.0 1.0" << std::endl;
	for (int k=1; k<=N; k++) // colors
		f << 1 + .5*sin(k*dphi) << " " << 1 + .5*cos(k*dphi) << " " << 1 + .5*sin(2.*k*dphi) << std::endl;

	f << "#field index" << std::endl;
	for (int k=1; k<=N; k++) { // indices
		knext = (k+1 > N) ? 1 : k+1;

		f << 0 << "\n" << k << "\n" << knext << "\n";
	}

	f.close();
}


void GravitySim::GravitySystem::update() {
	// for some reason, the first iteration seems to make the simulation explode
	if (running) {
		this->update_gravity(scene);
		this->update_bodies(scene);
	} else {
		running = true;
	}
}

void GravitySim::GravitySystem::update_gravity(Scene* scene) {
	auto query = scene->query_entities().with_component<Body>(scene).results;

	for (uint32_t& ea : query) {
		Body* a = scene->get_component<Body>(ea);

		for (uint32_t& eb : query) {
			if (eb != ea) {
				Body* b = scene->get_component<Body>(eb);

				vec3 w = b->position + -a->position;
				vec3 u = vec3::normalize(w);
				float d = w.magnitude();
				if ( d > 0.0f ) {
					a->force += u * (G * (a->mass * b->mass) / (d*d));
				} else {
					continue; // idk do something else
				}
			}
		}
	}
}

void GravitySim::GravitySystem::update_bodies(Scene* scene) {
	auto query = scene->query_entities().with_component<Body>(scene).results;

	for (uint32_t& ea : query) {
		Body* a = scene->get_component<Body>(ea);
		Transform* t = scene->get_component<Transform>(ea);

		a->acceleration = a->force * (1 / a->mass);
		a->velocity += a->acceleration;
		a->position += (a->velocity * dt);
		if (t != nullptr) t->position += (a->velocity * this->dt);
		a->force = vec3();
	}
}
