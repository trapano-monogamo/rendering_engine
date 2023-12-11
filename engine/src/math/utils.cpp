#include "math/utils.hpp"

// rad : pi = deg : 180

float deg_to_rad(float degrees) {
	return (degrees * PI) / 180.0;
}

float rad_to_deg(float radians) {
	return (radians * 180.0) / PI;
}
