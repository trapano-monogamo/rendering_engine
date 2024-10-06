#pragma once

#include "core/game_app.hpp"
#include "math/mat.hpp"

class LSScene : public GameApp {
private:
	float x0 = 3.f;
	float y0 = -4.f;
	float timestep = 0.1f;
	unsigned int steps = 20;
	//std::vector<Matrix<float>> points;

public:
	LSScene(const char* title, int width, int height);
	LSScene(LSScene&) = default;
	~LSScene() = default;

	void on_create() override;
	void on_update(float) override;
};
