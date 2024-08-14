#pragma once

#include "core/game_app.hpp"

class GOScene : public GameApp {
private:
	float camera_speed = 2.0f;

public:
	GOScene(const char* title, int width, int height);
	GOScene(GOScene&) = default;
	~GOScene() { /* ... */ }

	void on_create() override;
	void on_update(float) override;
};
