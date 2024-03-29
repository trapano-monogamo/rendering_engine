#include "core/game_app.hpp"
#include "GLFW/glfw3.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow*, int width, int height) {
	glViewport(0, 0, width, height);
}


/* TODO: handle fail case when creating the GLFWwindow
 * 	     and initializing GLAD
 * */
GameApp::GameApp(const char* title, int width, int height)
	: scene(Scene())
	, window(NULL)
	, width(width)
	, height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
		// return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
		// return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

GameApp::~GameApp() {
	glfwTerminate();
}

// TODO: InputHandler

void GameApp::run() {
	this->on_create();

	float t1, t2, dt = 0.0;
	while (!glfwWindowShouldClose(window)) {
		t2 = glfwGetTime();
		dt = t2 - t1;
		t1 = t2;

		this->on_update(dt);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
