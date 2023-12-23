#pragma once

#include <array>

struct vec3 {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
		struct {
			float v[3];
		};
	};

	vec3();
	vec3(vec3& v) = default;
	vec3(float x1, float x2, float x3);
	vec3(std::array<float, 3> v);

	float& operator[](int i);

	float magnitude();
	static float distance(vec3 a, vec3 b);

	void normalize();
	static vec3 normalize(vec3 a);

	static float angle(vec3 a, vec3 b);
	void rotate(vec3 axis, float angle);

	friend vec3 operator+(vec3 a, vec3 b);
	friend vec3 operator*(vec3 a, float x);
	friend vec3 operator-(vec3 a);
	void operator+=(vec3 a);
	void operator*=(float x);

	static float dot(vec3 a, vec3 b);
	static vec3 cross(vec3 a, vec3 b);
};

#define VEC3_X (vec3(1.0, 0.0, 0.0))
#define VEC3_Y (vec3(0.0, 1.0, 0.0))
#define VEC3_Z (vec3(0.0, 0.0, 1.0))


struct vec4 {
	union {
		struct {
			float x,y,z,w;
		};
		struct {
			float r,g,b,a;
		};
		struct {
			float v[4];
		};
	};

	vec4();
	vec4(vec4& v) = default;
	vec4(vec3& v, float x4);
	vec4(float x1, float x2, float x3, float x4);
	vec4(std::array<float, 4> v);

	float& operator[](int i);

	float magnitude();
	void normalize();
	static vec4 normalize(vec4 a);

	friend vec4 operator+(vec4 a, vec4 b);
	friend vec4 operator*(vec4 a, float x);
	friend vec4 operator-(vec4 a);
	void operator+=(vec4 a);
	void operator*=(float x);

	static float dot(vec4 a, vec4 b);
};


/*
struct vec2 {
	union {
		struct {
			float x, y;
		};
		struct {
			float u, v;
		};
	};

	vec2() = default;
	vec2(vec2& v) = default;
	vec2(float x1, float x2);

	float magnitude();
	void normalize();

	friend vec2 operator+(vec2 a, vec2 b);
	friend vec2 operator*(vec2 a, float x);
	friend vec2 operator-(vec2 a);
	void operator+=(vec2 a);
	void operator*=(float x);

	static float dot(vec2 a, vec2 b);
	static vec3 cross(vec2 a, vec2 b);
};
*/
