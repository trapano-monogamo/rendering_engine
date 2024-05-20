#pragma once

#include "common.hpp"
#include "ecs/ecs.hpp"
#include "core/camera.hpp"
#include "input_handler/input_hanlder.hpp"
#include "resource_manager/resource_manager.hpp"

struct ObjectRenderingOptions : public Component {
private:
	struct CullFaceOpt {
		bool active = true;
		GLenum order = GL_FRONT;
	};

public:
	CullFaceOpt cull_face;
	bool wireframe = false;

	ObjectRenderingOptions() = default;
	ObjectRenderingOptions(CullFaceOpt cull_face, bool wireframe)
		: cull_face(cull_face), wireframe(wireframe) {}

	void set();
};

struct SceneRenderingOptions {
	GLbitfield clear_buffer = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

	void set();
};

class Scene : public ECS, public ResourceManager {
public:
	Camera camera;
	InputHandler input_handler;
	SceneRenderingOptions rendering_options;
	vec3 background_color;

public:
	Scene();
	~Scene() = default;

	void render();
	void update(); // ECS::update(), InputHandler::update()

	void bind_window(GLFWwindow* window);
};
