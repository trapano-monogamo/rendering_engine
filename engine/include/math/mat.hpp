#pragma once

#include "math/vec.hpp"
#include <array>

struct mat4 {
	float m[16];

	mat4() = default;
	mat4(mat4& m) = default;
	mat4(std::array<float, 16>);

	static mat4 zeros();
	static mat4 identity();

	float operator[](int i);

	friend mat4 operator*(mat4 a, mat4 b);
	friend mat4 operator*=(mat4 a, mat4 b);

	void transpose();
	static mat4 transpose(mat4 m);

	static mat4 translation(vec3 pos);
	static mat4 scale(vec3 scale);
	static mat4 rotation(vec3 axis, float angle);
	static mat4 transform(vec3 scale, vec3 rotation_axis, float angle, vec3 translation);

	static mat4 ortho();
	static mat4 perspective(float fovy, float aspect_ratio, float near, float far);

	static mat4 lookat(vec3 pos, vec3 up, vec3 right, vec3 dir);
};
