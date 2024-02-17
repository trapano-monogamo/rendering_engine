#include "math/mat.hpp"
#include "math/utils.hpp"
#include "math/vec.hpp"
#include <cmath>

mat4::mat4(std::array<float, 16> _m) {
	for (int i = 0; i<16; i++) m[i] = _m[i];
}

mat4 mat4::identity() {
	return mat4({
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0,
	});
}

float& mat4::operator[](int i) {
	return this->m[i];
}

vec4 mat4::column(int i) {
	return vec4(
		this->m[0 * 4 + i],
		this->m[1 * 4 + i],
		this->m[2 * 4 + i],
		this->m[3 * 4 + i]
	);
}

vec4 mat4::row(int i) {
	return vec4(
		this->m[i * 4 + 0],
		this->m[i * 4 + 1],
		this->m[i * 4 + 2],
		this->m[i * 4 + 3]
	);
}


// ..:: operations ::..

void mat4::transpose() {
	mat4 temp = mat4(*this);
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			this->m[i*4 + j] = temp.m[j*4 + i];
}

mat4 mat4::transpose(mat4 m) {
	mat4 res = mat4();
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			res.m[i*4 + j] = m.m[j*4 + i];
	return res;
}

mat4 operator*(mat4 a, mat4 b) {
	mat4 res = mat4();
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			for (int k=0; k<4; k++)
				res.m[i*4 + j] += (a[i*4 + k] * b[k*4 + j]);
		}
	}
	return res;
}

vec4 operator*(mat4 m, vec4 v) {
	vec4 res(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res[i] += (v[j] * m.row(i)[j]);
		}
	}
	return res;
}


// ..:: transformations ::..


mat4 mat4::translation(vec3 p) {
	return mat4({
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		p.x, p.y, p.z, 1.0,
	});
}
mat4 mat4::scale(vec3 s) {
	return mat4({
		s.x, 0.0, 0.0, 0.0,
		0.0, s.y, 0.0, 0.0,
		0.0, 0.0, s.z, 0.0,
		0.0, 0.0, 0.0, 1.0,
	});
}
mat4 mat4::rotation(vec3 u, float a) {
	float cos_a = std::cos(a);
	float sin_a = std::sin(a);

	if (u.magnitude() == 0.0) { u = vec3(1.0, 0.0, 0.0); }
	u.normalize();
	float ux = u.x;
	float uy = u.y;
	float uz = u.z;

	return mat4({
		cos_a + ux*ux * (1-cos_a),     ux*uy * (1-cos_a) - uz*sin_a,    ux*uz * (1-cos_a) + uy*sin_a, 0.0,
		uy*ux * (1-cos_a) + uz*sin_a,  cos_a + uy*uy * (1-cos_a),       uy*uz * (1-cos_a) - ux*sin_a, 0.0,
		uz*ux * (1-cos_a) - uy*sin_a,  uz*uy * (1-cos_a) + ux*sin_a,    cos_a + uz*uz * (1-cos_a),    0.0,
		0.0,                           0.0,                             0.0,                          1.0
	});
}
mat4 mat4::rotation(vec3 euler_angles) {
	return mat4::rotation(VEC3_X, euler_angles[0]) * mat4::rotation(VEC3_Y, euler_angles[1]) * mat4::rotation(VEC3_Z, euler_angles[2]);
}

mat4 mat4::transform(vec3 scale, vec3 rotation_axis, float angle, vec3 translation) {
	return (mat4::scale(scale) * mat4::rotation(rotation_axis, angle)) * mat4::translation(translation);
}

mat4 mat4::transform(vec3 scale, vec3 euler_angles, vec3 translation) {
	return (mat4::scale(scale) * mat4::rotation(euler_angles)) * mat4::translation(translation);
}


mat4 mat4::ortho(float n, float f, float l, float r, float t, float b) {
	return mat4::transpose(mat4({
		2/(r-l), 0.0, 0.0, -(r+l)/(r-l),
		0.0, 2/(t-b), 0.0, -(t+b)/(t-b),
		0.0, 0.0, -2/(f-n), -(f+n)/(f-n),
		0.0, 0.0, 0.0, 1.0,
	}));
}

mat4 mat4::perspective(float fovy, float ar, float n, float f) {
	float t = std::tan(fovy/2.0)*n;
	float b = -t;
	float r = t * ar;
	float l = b;
	return mat4({
		2*n/(r-l), 0.0, 0.0, 0.0,
		0.0, 2*n/(t-b), 0.0, 0.0,
		(r+l)/(r-l), (t+b)/(t-b), -(f+n)/(f-n), -1.0,
		0.0, 0.0, -2*f*n/(f-n), 0.0,
	});
}


mat4 mat4::lookat(vec3 eye, vec3 up, vec3 right, vec3 dir) {
	up.normalize();
	right.normalize();
	dir.normalize();
	return mat4::transpose(mat4({
		right.x, right.y, right.z, -vec3::dot(right, eye),
		up.x, up.y, up.z, -vec3::dot(up, eye),
		-dir.x, -dir.y, -dir.z, -vec3::dot(-dir, eye),
		0.0, 0.0, 0.0, 1.0
	}));
	/*
	         | right.xyz   0 |   | 1 0 0 -p.x |
	lookat = | up.xyz      0 | * | 0 1 0 -p.y |
	         | dir.xyz     0 |   | 0 0 1 -p.z |
	         | 0   0   0   1 |   | 0 0 0   1  |
	*/
}
