#include "input_handler/input_hanlder.hpp"

InputHandler::InputHandler(GLFWwindow* window)
	: window(window)
	// , key_bindings(std::unordered_map<Key,Action>(
	// 		Key{ .code = GLFW_KEY_ESCAPE, .type = Key::Type::KEYBOARD },
	// 		// std::function<void()>([=]{ glfwSetWindowShouldClose(window, true); })
	// 		nullptr
	// 	))
{
	for (int i = 0; i < GLFW_KEY_LAST; i++)
		keys[i] = false;

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		mouse_buttons[i] = false;
}

void InputHandler::bind_window(GLFWwindow* window) {
	this->window = window;
}

void InputHandler::update() {
	for (int i = 0; i < GLFW_KEY_LAST; i++)
		keys[i] = (glfwGetKey(window, i) == GLFW_PRESS);

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		mouse_buttons[i] = (glfwGetMouseButton(window, i) == GLFW_PRESS);
	
	// for (auto& binding : key_bindings) {
	// 	if (keys[binding.first.code]) binding.second();
	// }
}

// void InputHandler::bind_key(Key k, Action c) { }

bool InputHandler::is_key_pressed(int key) {
	return keys[key];
}

bool InputHandler::is_mouse_btn_pressed(int btn) {
	return mouse_buttons[btn];
}
