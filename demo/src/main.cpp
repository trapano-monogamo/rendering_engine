#include "common.hpp"

#include <iostream>
#include <cmath>

#include "core/vertex_array.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "math/utils.hpp"
#include "math/mat.hpp"
#include "math/vec.hpp"

bool wireframe_mode = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
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

	// ..:: DEFINITIONS ::..
	// float vertices[] = {
	// 	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	// 	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	// 	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	// 	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	// };
	// unsigned int indices[] = {
	// 	0, 1, 3,
	// 	1, 2, 3,
	// };
	// float vertices[] = {
	// 	-0.5, -0.5,  0.5,  1.0, 0.0, 0.0,  1.0, 0.0,  //0
    //      0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  0.0, 1.0,  //1
    //     -0.5,  0.5,  0.5,  0.0, 0.0, 1.0,  0.0, 0.0,  //2
    //      0.5,  0.5,  0.5,  1.0, 0.0, 0.0,  1.0, 1.0,  //3
    //     -0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  1.0, 0.0,  //4
    //      0.5, -0.5, -0.5,  0.0, 0.0, 1.0,  0.0, 1.0,  //5
    //     -0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  0.0, 0.0,  //6
    //      0.5,  0.5, -0.5,  0.0, 1.0, 0.0,  1.0, 1.0,  //7
	// };
	// unsigned int indices[] = {
	// 	//Top
	// 	2, 6, 7,
	// 	2, 3, 7,
	// 	//Bottom
	// 	0, 4, 5,
	// 	0, 1, 5,
	// 	//Left
	// 	0, 2, 6,
	// 	0, 4, 6,
	// 	//Right
	// 	1, 3, 7,
	// 	1, 5, 7,
	// 	//Front
	// 	0, 2, 3,
	// 	0, 1, 3,
	// 	//Back
	// 	4, 6, 7,
	// 	4, 5, 7,
	// };
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0, 1.0, 0.0,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0, 0.0, 1.0,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0, 0.0, 0.0,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0, 1.0, 0.0,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0, 0.0, 1.0,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  1.0, 0.0, 0.0,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 0.0, 0.0,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0, 0.0, 1.0,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0, 0.0, 0.0,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0, 1.0, 0.0,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0, 0.0, 1.0,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0, 0.0, 0.0,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0, 1.0, 0.0,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0, 0.0, 1.0,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0, 1.0, 0.0,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0, 0.0, 1.0,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0, 0.0, 0.0,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0, 0.0, 1.0,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  1.0, 0.0, 0.0,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0, 1.0, 0.0,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 0.0, 0.0,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0, 0.0, 1.0,  0.0f, 1.0f
	};
	VertexArray va = VertexArray();
	va.write_buffers(vertices, sizeof(vertices), nullptr, 0);
	va.enable_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	va.enable_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	va.enable_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	mat4 transform = mat4::transform(
		vec3(1.0, 0.5, 1.0),
		vec3(0.0f, 1.0f, 1.0f),
		deg_to_rad(69),
		vec3(0.0, 0.0, 0.0)
	);
	mat4 projection = mat4::perspective(deg_to_rad(90.0), 1.0, 0.1f, 100.0f);
	mat4 view = mat4::lookat(vec3(0.0, 0.0, 5.0), VEC3_Y, VEC3_X, -VEC3_Z);

	Shader program = Shader("/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/vertex.shader", "/home/chiara/dev/cpp/rendering_engine/engine/assets/shaders/fragment.shader");
	program.set_uniform_matrix_4fv("transform", transform.m);
	program.set_uniform_matrix_4fv("projection", projection.m);
	program.set_uniform_matrix_4fv("view", view.m);

	Texture texture = Texture("/home/chiara/dev/cpp/rendering_engine/engine/assets/textures/container.jpg");

	float t = 0.0f;

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




	/* TODO  --  before abstracting a renderable and the scene
	 *
	 *
	 * 1. [x] provide x,y,z unit vectors in vec.hpp
	 *
	 * 2. [x] change rotation matrix to accept a vector (non-normalized) as direction, and an angle
	 *        (using the magnitude of the axis as angle value isn't convenient for the user)
	 *
	 * 4. [/] write functions to get angle of and rotate vec3 in vec.hpp
	 *
	 * 6. [/] write orthogonal and perspective projection matrices
	 *
	 * 7. [x] write camera matrix
	 *
	 * 8. [ ] write camera class (and write methods for moving and looking around)
	 *
	 * */




	// ..:: LOOP ::..
	while (!glfwWindowShouldClose(window)) {
		// input
		process_input(window);

		// rendering
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		t += 0.01;

		for (unsigned int i = 0; i < 10; i++) {
			transform = mat4::transform(
				vec3(1.0, 1.0, 1.0),
				positions[i],
				t,
				positions[i]
			);
			// view = mat4::lookat(vec3(0.0, 1.0, 1.0), vec3(0.0, 1.0, -1.0), vec3(1.0, 0.0, 0.0), -vec3(0.0, 1.0, 1.0));
			view = mat4::lookat(vec3(0.0, 0.0, 3.0), vec3(0.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0), -vec3(0.0, 0.0, 1.0));
			program.set_uniform_matrix_4fv("transform", transform.m);
			program.set_uniform_matrix_4fv("view", view.m);

			texture.use();
			va.use();
			program.use();
			// glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
