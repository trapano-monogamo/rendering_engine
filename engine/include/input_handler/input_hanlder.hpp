#pragma once

#include "common.hpp"
#include "math/vec.hpp"

#include <functional>
#include <unordered_map>

struct Key {
	int code;
	enum Type {
		KEYBOARD = 0, MOUSE
	} type;
};

// typedef std::function<void()> Action;
// typedef void(*Action)();

class InputHandler {
private:

	GLFWwindow* window;
	// std::unordered_map<Key, Action> key_bindings;

	bool keys[GLFW_KEY_LAST];
	bool mouse_buttons[GLFW_MOUSE_BUTTON_LAST];
	vec2 mouse_position;

public:
	InputHandler(GLFWwindow*);
	~InputHandler() = default;

	void bind_window(GLFWwindow*);

	void update();
	vec2 get_mouse_position() const;
	// void bind_key(Key k, Action c);
	
	bool is_key_pressed(int key);
	bool is_mouse_btn_pressed(int btn);
};
