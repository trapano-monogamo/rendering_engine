#pragma once

#include "common.hpp"
#include "core/scene.hpp"
#include <vector>

class GameApp {
protected:
	// std::vector<Scene> scenes;
	Scene scene;
	GLFWwindow* window;
	int width, height;

public:
	GameApp(const char* title, int width, int height);
	~GameApp();

	virtual void on_create() = 0;
	virtual void on_update(float dt) = 0;

	void run();
};
