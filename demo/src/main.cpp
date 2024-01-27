#include "common.hpp"

#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>

#include "core/transform.hpp"
#include "core/renderable.hpp"
#include "core/scene.hpp"
#include "core/vertex_array.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/camera.hpp"
#include "math/utils.hpp"
#include "math/mat.hpp"
#include "math/vec.hpp"
#include "ecs/ecs.hpp"

bool wireframe_mode = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		wireframe_mode = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		wireframe_mode = false;
	}
}



struct Rotating : public Component {};

struct Body : public Component {
	float mass;
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	vec3 force;

	Body(float m, vec3 p, vec3 v, vec3 a, vec3 f)
		: mass(m), position(p), velocity(v), acceleration(a), force(f)
	{}
};

class GravitySystem : public System {
public:
	Scene* scene;
	float dt;
	float G = 0.3f;

	GravitySystem() : scene(nullptr), dt(0.0f) {}

public:
	void update() override {
		this->update_gravity(scene);
		this->update_bodies(scene, dt);
	}

	void update_gravity(Scene* scene) {
		auto query = scene->query_entities().with_component<Body>(scene).results;

		for (uint32_t& ea : query) {
			Body* a = scene->get_component<Body>(ea);

			for (uint32_t& eb : query) {
				if (eb != ea) {
					Body* b = scene->get_component<Body>(eb);

					float r = std::abs(vec3::distance(a->position, b->position));
					if ( r > 0.0f ) {
						a->force += vec3::normalize(b->position + -a->position) * (G * (a->mass * b->mass) / (r*r));
					} else {
						continue; // idk do something else
					}
				}
			}
		}
	}

	void update_bodies(Scene* scene, float dt) {
		auto query = scene->query_entities().with_component<Body>(scene).results;

		for (uint32_t& ea : query) {
			Body* a = scene->get_component<Body>(ea);

			a->acceleration = a->force * (1 / a->mass);
			a->velocity += a->acceleration;
			a->position += a->velocity * dt;
			a->force = vec3();
		}
	}
};

class UpdateTransforsSystem : public System {
public:
	Scene* scene;

	UpdateTransforsSystem() : scene(nullptr) {}

public:
	void update() override {
		auto query = scene->query_entities()
			.with_component<Body>(scene)
			.with_component<Transform>(scene)
			.results;

		for (auto e : query) {
			Body* b = scene->get_component<Body>(e);
			Transform* t = scene->get_component<Transform>(e);
			t->position = b->position;
		}
	}
};



int main() {
	// ..:: INITIALIZATION ::..
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1500, 1500, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);




	/* TODO:
	 *
	 * 1. [x] introduce ECS
	 *
	 * 2. [x] make renderable and transform into components
	 *
	 * 3. [ ] make camera into component
	 *
	 * 4. [ ] write resource manager
	 *
	 * 5. [ ] write input manager
	 *
	 * */




	// ..:: DEFINITIONS ::..

	float speed = 2.5f;

	Scene scene = Scene();
	scene.camera = Camera(vec3(0.0, 0.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);

	GravitySystem* gravity_system = new GravitySystem();
	gravity_system->scene = &scene;
	UpdateTransforsSystem* update_transforms_system = new UpdateTransforsSystem();
	update_transforms_system->scene = &scene;
	scene.add_system(gravity_system);
	scene.add_system(update_transforms_system);
	
	// Renderable* sphere = new Renderable();
	// sphere->default_sphere(6, 10);
	// Transform* st = new Transform();
	// st->translate(vec3(0.0, 3.0, 0.0));
	// uint32_t sid = scene.add_entity();
	// scene.add_component<Renderable>(sid, sphere);
	// scene.add_component<Transform>(sid, st);

	// add floor
	float vertices[] = {
		-0.5,  0.0, -0.5,   0.5, 0.5, 0.5,   0.0, 0.0,
		 0.5,  0.0, -0.5,   0.5, 0.5, 0.5,   1.0, 0.0,
		 0.5,  0.0,  0.5,   0.5, 0.5, 0.5,   1.0, 1.0,
		-0.5,  0.0,  0.5,   0.5, 0.5, 0.5,   0.0, 1.0, };
	unsigned int indices[] = {
		0, 1, 2,
		2, 0, 3, };
	Transform* floor_t = new Transform();
	floor_t->translate(vec3(0.0, -10.0, 0.0));
	floor_t->resize(vec3(500.0, 0.0, 500.0));
	VertexArray va = VertexArray();
	va.write_buffers(vertices, sizeof(vertices), indices, sizeof(indices));
	va.enable_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	va.enable_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	va.enable_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	Shader shader = Shader();
	LOG_ERROR(shader.load_source_files("/home/chiara/dev/cpp/rendering_engine/demo/src/vertex.shader", "/home/chiara/dev/cpp/rendering_engine/demo/src/fragment.shader"));
	Texture texture = Texture("/home/chiara/dev/cpp/rendering_engine/engine/assets/textures/checkboard.png");
	texture.with_parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	texture.with_parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	texture.with_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	texture.with_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	Renderable* floor = new Renderable();
	floor->load_va(va);
	floor->load_shader(shader);
	floor->load_texture(texture);

	uint32_t id = scene.add_entity();
	scene.add_component<Transform>(id, floor_t);
	scene.add_component<Renderable>(id, floor);
	
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
	for (int i = 0; i < sizeof(positions) / sizeof(vec3); i++) {
		Renderable* obj = new Renderable();
		obj->default_cube();

		Transform* t = new Transform();
		t->translate(positions[i]);
		// t->resize(vec3(1,1,1) * ( .5 + .5 * masses[i]));

		Body* b = new Body{ masses[i], positions[i], velocities[i], vec3(), vec3() };

		uint32_t id = scene.add_entity();
		scene.add_component<Renderable>(id, obj);
		scene.add_component<Transform>(id, t);
		scene.add_component<Body>(id, b);
	}



	/* TODO
	 *
	 * [ ] Renderable should provide its own draw function
	 *
	 * */


	// error 1282 before first scene.render() call



	// ..:: LOOP ::..

	float a = 0.0f;
	float t1, t2, dt = 0.0;

	while (!glfwWindowShouldClose(window)) {
		// dt
		float t2 = glfwGetTime();
		dt = t2 - t1;
		t1 = t2;

		gravity_system->dt = dt;
		scene.update();

		// input
		process_input(window);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
			scene.camera.pos += (u * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
			scene.camera.pos += (-u * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			scene.camera.pos += (-scene.camera.right * speed * dt);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			scene.camera.pos += (scene.camera.right * speed * dt);
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			scene.camera.rotate(speed/1.8 * dt, 0.0);
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			scene.camera.rotate(-speed/1.8 * dt, 0.0);
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			scene.camera.rotate(0.0, speed/1.8 * dt);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			scene.camera.rotate(0.0, -speed/1.8 * dt);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			scene.camera.translate(VEC3_Y * speed * dt);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			scene.camera.translate(-VEC3_Y * speed * dt);

		// clearing screen and depth buffer
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw mode
		if (wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		a += 0.01;

		mat4 view = mat4::lookat(scene.camera.pos, scene.camera.up, scene.camera.right, scene.camera.dir);

		// auto gravity_query = scene.query_entities()
		// 	.with_component<Body>(&scene)
		// 	.with_component<Transform>(&scene)
		// 	.results;
		// for (auto& entity : gravity_query) {
		// 	Transform* t = scene.get_component<Transform>(entity);
		// 	Body* b = scene.get_component<Body>(entity);
		// 	t->position = b->position;
		// }

		scene.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
