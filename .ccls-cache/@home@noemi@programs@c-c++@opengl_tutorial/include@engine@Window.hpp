#pragma once
#include "common_opengl.hpp"

namespace eng
{


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window {
private:
	 bool wireframe_mode;
	 
public:
	 GLFWwindow* window;

	 Window(int width, int height, const char* title = "Hello OpenGL", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	 virtual ~Window();

	 void run();

	 virtual void process_input();
	 virtual void on_create();
	 virtual void on_update(float elapsed_time);
};


}
