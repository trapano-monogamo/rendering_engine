#pragma once

#include "core/game_app.hpp"

class LightingScene : public GameApp {
private:
	float camera_speed = 2.0f;
	vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
	float t = 0.0f;
	unsigned int source_id;

public:
	LightingScene(const char* title, int width, int height);
	LightingScene(LightingScene&) = default;
	~LightingScene() { /* ... */ }

	void on_create() override;
	void on_update(float) override;
};
