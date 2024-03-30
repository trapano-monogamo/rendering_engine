// #include "lighting.hpp"
// #include "scenes.hpp"

#include "math/types.hpp"
#include <iostream>

int main() {
	mat4 m(std::array<float,16>{
		1.0, 0.0, 2.0, 5.0,
		0.0, 1.0, 0.0, 0.0,
		7.0, 0.0, 1.0, 0.0,
		9.0, 0.0, 0.0, 1.0f
	});

	std::cout << m * mat4::transpose(m);
	
	// LightingScene app = LightingScene("PP", 1000, 1000);
	// app.run();

	return 0;
}
