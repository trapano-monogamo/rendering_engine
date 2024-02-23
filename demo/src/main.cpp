/* ~ TODO ~
 *
 * - introduce textures:
 *   - sampling in the shader:
 *   	- check renderable keys (if there's no texture)
 *   - loading from file
 *
 * - introduce materials:
 *   - usage in the shader:
 *   	- check renderable keys (if there's no material)
 *   - loading from file
 *   - lighting:
 *   	- entities with LightSource component
 *   	- scene queries for those components and computes the light data to send to the shader as uniforms
 *
 * - tidy up ECS and ResourceManager:
 *   - ECS:
 *   	- delete components
 *   	- better query entities and query components interfaces [OPTIONAL]
 *   - ResouceManager:
 *   	- unloading resources
 *   	- deleting resources (requires making sure the destructors
 *   	  of the Resource inheritors are set up correctly)
 *   	  	- on demand
 *   	  	- when needed ?
 *   	- caching [OPTIONAL, also... scary]
 *
 * - create Window/App class with:
 *   - array Scenes[]
 *   - fn on_create()
 *   - fn on_update()
 *
 * - provide default resources:
 *   - default shaders with appropriate uniforms:
 *   	- if lighting is going to be supported, build shaders to be included into other shaders
 *   	  to provide an easy way of implementing different lighting techniques
 *   - default textures [OPTIONAL]
 *   - default meshes (cube, sphere, square, circle, triangle, BEAN)
 *
 * - separation between 2D and 3D (???) [OPTIONAL]
 *
 * - physics module: (easier said than done...)
 *   - rigid body colliders (for default meshes and custom (1:1 with mesh or following other vertex data))
 *   - collision logic:
 *   	- collision detection (you bastard)
 *   	- collision response (conservation laws for physical rigid bodies)
 *   - joints (lol)
 *   - springs
 *   - skeletons:
 *   	- tree of transforms
 *   	- recursive transformations and forces
 *
 * - make project compile into a library and have the demo be a project that uses it
 *   rather than being part of the root project.
 *
 * */



#include "common.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#include <string>

#include "core/shader.hpp"
#include "core/transform.hpp"
#include "core/renderable.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "math/utils.hpp"
#include "math/vec.hpp"
#include "ecs/ecs.hpp"
#include "resource_manager/manager.hpp"

bool wireframe_mode = false;

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
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



void create_circle_mesh_file(const char* filename, int N) {
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
public:
	Scene* scene;
	float dt = 0.0f;
	float G = 0.3f;

	GravitySystem() : scene(nullptr), dt(0.0f) {}

	void update() override {
		this->update_gravity(scene);
		this->update_bodies(scene);
	}

	void update_gravity(Scene* scene) {
		auto query = scene->query_entities().with_component<Body>(scene).results;

		for (uint32_t& ea : query) {
			Renderable* r = scene->get_component<Renderable>(ea);
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

	void update_bodies(Scene* scene) {
		auto query = scene->query_entities().with_component<Body>(scene).results;

		for (uint32_t& ea : query) {
			Body* a = scene->get_component<Body>(ea);
			Renderable* r = scene->get_component<Renderable>(ea);

			a->acceleration = a->force * (1 / a->mass);
			a->velocity += a->acceleration;
			a->position += (a->velocity * dt);
			if (r != nullptr) r->position += (a->velocity * this->dt);
			a->force = vec3();
		}
	}
};



int main() {
	// ..:: INITIALIZATION ::..
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 1000, "LearnOpenGL", NULL, NULL);
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



	// ..:: DEFINITIONS ::..

	// create_circle_mesh_file("/home/chiara/dev/cpp/rendering_engine/engine/assets/meshes/circle.mesh", 20);

	float speed = 2.5f;
	
	Scene scene = Scene();

	scene.camera = Camera(vec3(0.0, 0.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);

	scene.register_resource("square_mesh",  "/home/chiara/dev/cpp/rendering_engine/engine/assets/meshes/square.mesh");
	scene.register_resource("basic_shader", "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/basic.shader");
	scene.register_resource("basic2_shader",  "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/basic2.shader");
	scene.register_resource("circle_mesh",  "/home/chiara/dev/cpp/rendering_engine/engine/assets/meshes/circle.mesh");

	auto test_shader = scene.get_resource<Shader>("basic2_shader");
	test_shader->set_uniform<float>("t", 1.f, Shader::UniformType::FLOAT, 1);

	GravitySystem* gravity_system = new GravitySystem();
	scene.add_system(gravity_system);
	gravity_system->scene = &scene;

	uint32_t id = scene.add_entity();
	Renderable* floor = new Renderable("square_mesh", "", "basic_shader", "");
	floor->translate(vec3(0.0, -5.0, 0.0));
	floor->rotate_euler(vec3(PI/2,0,0));
	floor->resize(vec3(10.0, 10.0, 0.0));
	scene.add_component<Renderable>(id, floor);

	// Texture texture = Texture("/home/chiara/dev/cpp/rendering_engine/engine/assets/textures/checkboard.png");
	// texture.with_parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	// texture.with_parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	// texture.with_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// texture.with_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
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

	float t = 10.f;

	for (int i = 0; i < (int)(sizeof(positions) / sizeof(vec3)); i++) {
		Renderable* obj = new Renderable("circle_mesh", "", "basic2_shader", "");
		obj->translate(positions[i]);

		Body* b = new Body{ masses[i], positions[i], velocities[i], vec3(), vec3() };

		uint32_t id = scene.add_entity();
		scene.add_component<Renderable>(id, obj);
		scene.add_component<Body>(id, b);
	}


	// ..:: LOOP ::..

	float t1, t2, dt = 0.0;

	while (!glfwWindowShouldClose(window)) {
		t2 = glfwGetTime();
		dt = t2 - t1;
		t1 = t2;

		t+=0.1f;
		scene.get_resource<Shader>("basic2_shader")->set_uniform("t", t, Shader::UniformType::FLOAT, 1);

		gravity_system->dt = dt;
		scene.update();

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

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		scene.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
