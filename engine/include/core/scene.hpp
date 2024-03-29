#pragma once

#include "common.hpp"
#include "ecs/ecs.hpp"
#include "core/camera.hpp"
#include "input_handler/input_hanlder.hpp"
#include "resource_manager/resource_manager.hpp"

struct RenderingOptions {
	bool wireframe = false;
	GLbitfield clear_buffer = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

	void set();
};

class Scene : public ECS, public ResourceManager {
public:
	Camera camera;
	InputHandler input_handler;
	RenderingOptions rendering_options;

public:
	Scene();
	~Scene() = default;

	void render();
	void update(); // ECS::update(), InputHandler::update()

	void bind_window(GLFWwindow* window);
};
