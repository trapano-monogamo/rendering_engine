#pragma once

struct vec3 {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
	};

	vec3() = default;
	vec3(vec3& v) = default;
	vec3(float x1, float x2, float x3);

	float magnitude();
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
