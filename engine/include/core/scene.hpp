#pragma once

#include "ecs/ecs.hpp"
#include "core/camera.hpp"

class Scene : public ECS {
public:
	Camera camera;

public:
	Scene();
	~Scene() = default;

	void render();
};
