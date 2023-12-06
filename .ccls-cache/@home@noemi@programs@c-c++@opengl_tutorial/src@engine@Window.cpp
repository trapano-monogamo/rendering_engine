#include "engine/Window.hpp"
#include "engine/Shader.hpp"
#include "engine/VertexArray.hpp"
#include "engine/Renderable.hpp"
#include "my_utils.hpp"
#include <iostream>

void eng::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	 glViewport(0, 0, width, height);
}

eng::Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	 glfwInit();
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 window = glfwCreateWindow(width, height, title, monitor, share);
	 if (window == nullptr) {
		  std::cout << "Failed to create window..." << std::endl;
		  glfwTerminate();
		  exit(-1);
	 }
	 glfwMakeContextCurrent(window);

	 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		  std::cout << "Failed to initialize GLAD..." << std::endl;
		  exit(-1);
	 }

	 glfwSetFramebufferSizeCallback(window, eng::framebuffer_size_callback);
}

eng::Window::~Window() {
	 std::cout << "Closing window..." << std::endl;
	 glfwTerminate();
}

void eng::Window::run() {
	 //float vertices[] = {
	 //	   0.5f,  0.5f, 0.0f,  1.0, 0.0, 0.0,  // top right
	 //	   0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  0.0, 0.0, 1.0,  // bottom left
    //    -0.5f,  0.5f, 0.0f,  1.0, 1.0, 1.0,  // top left
	 //};

	 //unsigned int indices[] = {
	 //	  0, 1, 3,
	 //	  1, 2, 3
	 //};

	 //glm::mat4 transform = glm::mat4(1.0f);
	 //transform = glm::translate(transform, glm::vec3(0.3f, 0.2f, 0.0f));
	 //transform = glm::rotate(transform, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	 //VertexArray va(sizeof(vertices), vertices, sizeof(indices), indices);
	 //Shader shader("../res/vertex.shader", "../res/fragment.shader");
	 //shader.set_uniform_matrix_4fv("transform", transform);

	 Renderable obj = Renderable();
	 obj.translate(glm::vec3(0.0f, 0.0f, -1.0f));
	 
	 this->on_create();

	 // ..:: Rendering Loop ::..
	 while (!glfwWindowShouldClose(this->window)) {
		  // ..:: Input ::..
		  this->process_input();
		  this->on_update(1.0f);

		  // ..:: Rendering ::..
		  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		  glClear(GL_COLOR_BUFFER_BIT);

		  if (this->wireframe_mode)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		  else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		  //shader.use();
		  //va.use();
		  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		  //unbind_all();

		  obj.draw();

		  // ..:: buffers and events ::..
		  glfwSwapBuffers(this->window);
		  glfwPollEvents();
	 }
}

void eng::Window::process_input() {
	 if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		  glfwSetWindowShouldClose(this->window,  true);

	 if (glfwGetKey(this->window, GLFW_KEY_TAB) == GLFW_PRESS)
		  this->wireframe_mode = true;
	 else
		  this->wireframe_mode = false;
}

void eng::Window::on_create() {}
void eng::Window::on_update(float elapsed_time) {}
