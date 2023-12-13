#include "common.hpp"

#include <iostream>
#include <cmath>
#include <vector>

#include "core/renderable.hpp"
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
	 * 2. [/] make renderable and transform into components
	 *
	 * 3. [ ] make camera into component
	 *
	 * 4. [ ] write resource manager
	 *
	 * 5. [ ] write input manager
	 *
	 * */




	// ..:: DEFINITIONS ::..
	// float vertices[] = {
	// 	-0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  0.0, 0.0,
	// 	 0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  1.0, 0.0,
	// 	 0.5,  0.5, -0.5,  0.0, 0.0, 1.0,  1.0, 1.0,
	// 	-0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  0.0, 1.0,
	// 	-0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  1.0, 1.0,
	// 	 0.5, -0.5,  0.5,  0.0, 0.0, 1.0,  0.0, 1.0,
	// 	 0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  0.0, 0.0,
	// 	-0.5,  0.5,  0.5,  0.0, 1.0, 0.0,  1.0, 0.0,
	// };
	// unsigned int indices[] = {
	// 	0, 1, 3, 3, 1, 2,
	// 	1, 5, 2, 2, 5, 6,
	// 	5, 4, 6, 6, 4, 7,
	// 	4, 0, 7, 7, 0, 3,
	// 	3, 2, 7, 7, 2, 6,
	// 	4, 5, 0, 0, 5, 1,
	// };
	// VertexArray va = VertexArray();
	// va.write_buffers(vertices, sizeof(vertices), indices, sizeof(indices));
	// va.enable_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// va.enable_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// va.enable_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Shader program = Shader("/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/vertex.shader", "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/fragment.shader");

	// Texture texture = Texture("/home/chiara/dev/cpp/rendering_engine/engine/assets/textures/container.jpg");
	
	// std::vector<Renderable> objects(10);
	// for (auto& obj : objects) obj.default_cube();
	
	Renderable obj = Renderable();
	obj.default_cube();

	vec3 positions[] = {
		vec3( 0.0f,  0.0f,  0.0f),
		vec3( 2.0f,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3( 2.4f, -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3( 1.3f, -2.0f, -2.5f),
		vec3( 1.5f,  2.0f, -2.5f),
		vec3( 1.5f,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	Camera camera = Camera(vec3(0.0, 0.0, 3.0))
		// .with_ortho(0.1, 100.0, -5.0, 5.0, 5.0, -5.0);
		.with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 100.0f);

	obj.program.set_uniform_matrix_4fv("projection", camera.projection.m);

	mat4 view, transform;

	float speed = 2.5f;

	// ..:: LOOP ::..
	
	float a = 0.0f;
	float t1, t2, dt = 0.0;

	while (!glfwWindowShouldClose(window)) {
		// dt
		float t2 = glfwGetTime();
		dt = t2 - t1;
		t1 = t2;

		// input
		process_input(window);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			vec3 u = vec3::normalize(vec3(camera.dir.x, 0.0, camera.dir.z));
			camera.pos += (u * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			vec3 u = vec3::normalize(vec3(camera.dir.x, 0.0, camera.dir.z));
			camera.pos += (-u * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.pos += (-camera.right * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.pos += (camera.right * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			camera.rotate(speed/1.8 * dt, 0.0);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			camera.rotate(-speed/1.8 * dt, 0.0);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			camera.rotate(0.0, speed/1.8 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			camera.rotate(0.0, -speed/1.8 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			camera.translate(VEC3_Y * speed * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			camera.translate(-VEC3_Y * speed * dt);
		}

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

		// camera.rotate(0.01f, 0.0f);
		// camera.pos.rotate(VEC3_X, 0.01f);
		// camera.pos = vec3::normalize(camera.pos) * (3.0f + std::sin(10.f*a));
		view = mat4::lookat(camera.pos, camera.up, camera.right, camera.dir);
		obj.program.set_uniform_matrix_4fv("view", view.m);

		// draw call for each cube
		for (unsigned int i = 0; i < 10; i++) {
			transform = mat4::transform(
				vec3(1.0, 1.0, 1.0),
				positions[i],
				a,
				positions[i]
			);
			obj.program.set_uniform_matrix_4fv("transform", transform.m);

			obj.texture.use();
			obj.va.use();
			obj.program.use();
			glDrawElements(GL_TRIANGLES, obj.va.elements_count, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
