#pragma once

#include <array>
#include <cmath>



template<typename T, int N, typename PRECISION_T = float>
class Vector {
public:
	T v[N];

public:
	Vector();
	Vector(Vector<T,N,PRECISION_T>&) = default;
	Vector(...);
	Vector(std::array<T,N> v);
	~Vector() = default;

	T& operator[](int i);

	// Vector lives in a vector space (V,||.||) no matter T.
	// Vector::magnitude() implements euclidean norm by default.
	// Note that this is going to cause an error for types that don't implement the necessary operations
	virtual PRECISION_T magnitude();
	static PRECISION_T distance(Vector a, Vector b);
	void normalize();
	static Vector normalize(Vector v);
	
	// (V, +, dot, *)
	// +: VxV -> V (with inverse -)
	// dot: VxV -> R
	// *: RxV -> V (with "inverse" being /)
	template<typename, int, typename> friend Vector operator+(Vector a, Vector b);
	template<typename, int, typename> friend Vector operator-(Vector a);
	template<typename, int, typename> friend Vector operator-(Vector a, Vector b);
	template<typename, int, typename> friend Vector operator*(Vector a, PRECISION_T x);
	void operator+=(Vector a);
	void operator*=(PRECISION_T x);
	static PRECISION_T dot(Vector a, Vector b);

	// should cross product be implemented?
};

template<typename T, int N, typename PRECISION_T = float>
class RealVector : public Vector<T, N, PRECISION_T> {
public:
	void rotate(RealVector<T,N,PRECISION_T> axis, PRECISION_T angle);
};

class Vec2f : public RealVector<float, 2, float> {};
class Vec2d : public RealVector<double, 2, double> {};
class Vec2i : public Vector<int, 2, float> {}; // for 2d grids

class Vec3f : public RealVector<float, 3, float> {};
class Vec3d : public RealVector<double, 3, double> {};
class Vec3i : public Vector<int, 3, float> {}; // for 3d grids

class Vec4f : public RealVector<float, 4, float> {};
class Vec4d : public RealVector<double, 4, double> {};



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

	void operator=(const vec3& a);
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

	void operator=(const vec2& a);

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
