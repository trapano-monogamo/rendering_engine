#pragma once

#include "ecs/ecs.hpp"
#include "core/camera.hpp"
#include "resource_manager/manager.hpp"

class Scene : public ECS, public ResourceManager {
public:
	Camera camera;

public:
	Scene();
	~Scene() = default;

	void render();
};
