#pragma once

#define PI (3.14159265359)

template<typename T> T clamp(T a, T b, T x) {
	return (x <= a) ? a : (x >= b) ? b : x;
}
template<typename T> T wrap(T a, T b, T x) {
	return a + (x % (b-a));
}

float deg_to_rad(float degrees);
float rad_to_deg(float radians);
