#pragma once

#include "math/vec.hpp"
#include <array>


template<unsigned int> class Vector;
template<unsigned int> class Covector;

template<unsigned int M, unsigned int N>
class Matrix {
private:
	float* m;

public:
	Matrix();
	Matrix(std::array<float, M*N>&&);
	Matrix(const Matrix<M,N>&);
	Matrix(Matrix<M,N>&&);
	virtual ~Matrix();

	// std::enable_if the mrix is squared => if M == N
	// template<unsigned int _N> static Matrix<_N,_N> identity();

	// std::enable_if the mrix is not Vector/Covector => if M != 1 || N != 1
	float& at(unsigned int, unsigned int);
	float get(unsigned int, unsigned int) const;

	// std::enable_if the mrix is Vector/Covector => if M == 1 || N == 1
	float& at(unsigned int);
	float get(unsigned int) const;

	float operator[](unsigned int) const;

	Vector<M> col(unsigned int j = 0) const;
	Covector<N> row(unsigned int i = 0) const;

	Matrix<N,M> transpose() const;

	// operations
	virtual void operator=(const Matrix<M,N>&);
	
	template<unsigned int _M, unsigned int _N>
		friend Matrix<_M,_N> operator+(const Matrix<_M,_N>&, const Matrix<_M,_N>&);
	template<unsigned int _M, unsigned int _N>
		friend Matrix<_M,_N> operator-(const Matrix<_M,_N>&, const Matrix<_M,_N>&);
	Matrix<M,N> operator-() const;
	void operator+=(const Matrix<M,N>&);
	void operator-=(const Matrix<M,N>&);

	template<unsigned int _M, unsigned int _N, unsigned int _P>
		friend Matrix<_M,_P> operator*(const Matrix<_M,_N>&, const Matrix<_N,_P>&);
	template<unsigned int _M, unsigned int _N>
		friend Matrix<_M,_N> operator*(float, const Matrix<_M,_N>&);

	operator vec2() const;
	operator vec3() const;

	// (std::enable_if square matrix)
	//  1. identity
	//  2. determinant
	//  3. trace
	//  4. eigenvalues
};

template<unsigned int M> class Vector   : public Matrix<M, 1> {
public:
	Vector() : Matrix<M,1>() {}
	Vector(std::array<float, M>&& arr) : Matrix<M,1>(std::move(arr)) {}
	Vector(const Matrix<M,1>& m) : Matrix<M,1>(m) {}
	Vector(Vector<M>&&) = default;

	void operator=(const Matrix<M,1>& v) override {
		for(unsigned int i=0; i<M; i++) this->at(i) = v[i];
	}
};

template<unsigned int N> class Covector : public Matrix<1, N> {
public:
	Covector() : Matrix<1,N>() {}
	Covector(std::array<float, N>&& arr) : Matrix<1,N>(std::move(arr)) {}
	Covector(const Matrix<1,N>& m) : Matrix<1,N>(m) {}
	Covector(Covector<N>&&) = default;

	void operator=(const Matrix<1,N>& v) override {
		for(unsigned int i=0; i<N; i++) this->at(i) = v[i];
	}
};


/* MATRIX IMPLEMENTATION */

template<unsigned int M, unsigned int N>
Matrix<M,N>::Matrix() {
	m = new float[M*N];
	for (unsigned int i=0; i<M*N; i++) m[i] = 0.f;
}

template<unsigned int M, unsigned int N>
Matrix<M,N>::Matrix(std::array<float, M*N>&& arr) {
	m = new float[M*N];
	for (unsigned int i=0; i<M*N; i++) m[i] = arr[i];
}

template<unsigned int M, unsigned int N>
Matrix<M,N>::Matrix(const Matrix<M,N>& a) {
	m = new float[M*N];
	for(unsigned int i=0; i<M*N; i++) m[i] = a[i];
}

template<unsigned int M, unsigned int N>
Matrix<M,N>::Matrix(Matrix<M,N>&& a) {
	m = new float[M*N];
	for(unsigned int i=0; i<M*N; i++) m[i] = a[i];
}

template<unsigned int M, unsigned int N>
Matrix<M,N>::~Matrix() { delete[] m; }

template<unsigned int M, unsigned int N>
float Matrix<M,N>::operator[](unsigned int idx) const {
	if (idx >= M*N) throw;
	else return m[idx];
}

template<unsigned int M, unsigned int N>
Vector<M> Matrix<M,N>::col(unsigned int j) const {
	Vector<M> v;
	for (unsigned int k=0; k<M; k++) v.at(k,1) = this->get(k,j);
	return v;
}

template<unsigned int M, unsigned int N>
Covector<N> Matrix<M,N>::row(unsigned int i) const {
	Covector<N> v;
	for (unsigned int k=0; k<N; k++) v.at(1,k) = this->get(i,k);
	return v;
}

template<unsigned int M, unsigned int N>
float& Matrix<M,N>::at(unsigned int i, unsigned int j) {
	if (i >= M || j >= N) throw;
	else return m[i * N + j];
}

template<unsigned int M, unsigned int N>
float& Matrix<M,N>::at(unsigned int i) {
	if (i >= M*N) throw;
	else return m[i];
}

template<unsigned int M, unsigned int N>
float Matrix<M,N>::get(unsigned int i, unsigned int j) const {
	if (i >= M || j >= N) throw;
	else return m[i * N + j];
}

template<unsigned int M, unsigned int N>
float Matrix<M,N>::get(unsigned int i) const {
	if (i >= M*N) throw;
	else return m[i];
}

// template<unsigned int M, unsigned int N>
// Vector<M> Matrix<M,N>::col(unsigned int j) {}
// 
// template<unsigned int M, unsigned int N>
// Covector<N> Matrix<M,N>::row(unsigned int i) {}

template<unsigned int M, unsigned int N>
Matrix<N,M> Matrix<M,N>::transpose() const {
	Matrix<N,M> res;
	for (unsigned int i=0; i<N; i++)
		for (unsigned int j=0; j<M; j++)
			res.at(i,j) = this->get(j,i);
	return res;
}

template<unsigned int M, unsigned int N>
void Matrix<M,N>::operator=(const Matrix<M,N>& a) {
	if (m) delete[] m;
	m = new float[M*N];
	for (unsigned int i=0; i<M*N; i++) m[i] = a[i];
}

template<unsigned int M, unsigned int N>
Matrix<M,N> operator+(const Matrix<M,N>& a, const Matrix<M,N>& b) {
	Matrix<M,N> res;
	for (unsigned int i=0; i<M*N; i++) res.at(i) = a[i] + b[i];
	return res;
}

template<unsigned int M, unsigned int N>
Matrix<M,N> operator-(const Matrix<M,N>& a, const Matrix<M,N>& b) {
	Matrix<M,N> res;
	for (unsigned int i=0; i<M*N; i++) res.at(i) = a[i] - b[i];
	return res;
}

template<unsigned int M, unsigned int N>
Matrix<M,N> Matrix<M,N>::operator-() const {
	Matrix<M,N> res;
	for (unsigned int i=0; i<M*N; i++) res.at(i) = m[i] * -1.f;
	return res;
}

template<unsigned int M, unsigned int N>
void Matrix<M,N>::operator+=(const Matrix<M,N>& a) {
	for (unsigned int i=0; i<M*N; i++) m[i] += a[i];
}

template<unsigned int M, unsigned int N>
void Matrix<M,N>::operator-=(const Matrix<M,N>& a) {
	for (unsigned int i=0; i<M*N; i++) m[i] -= a[i];
}

template<unsigned int _M, unsigned int _N, unsigned int _P>
Matrix<_M,_P> operator*(const Matrix<_M,_N>& a, const Matrix<_N,_P>& b) {
	Matrix<_M,_P> res;
	for (unsigned int i=0; i<_M; i++)
		for (unsigned int j=0; j<_P; j++)
			for (unsigned int k=0; k<_N; k++)
				res.at(i,j) += a.get(i,k) * b.get(k,j);
	return res;
}

template<unsigned int _M, unsigned int _N>
Matrix<_M,_N> operator*(float x, const Matrix<_M,_N>& a) {
	Matrix<_M,_N> res;
	for (unsigned int i=0; i<_M*_N; i++) res.at(i) = a[i] * x;
	return res;
}




/* the following types are for legacy reasons... LOL */

struct mat4 {
	float m[16];

	mat4() = default;
	mat4(mat4&) = default;
	mat4(std::array<float, 16>);

	void operator=(const mat4&);

	static mat4 zeros();
	static mat4 identity();

	float& operator[](int i);
	vec4 column(int i);
	vec4 row(int i);

	friend mat4 operator*(mat4 a, mat4 b);
	friend mat4 operator*=(mat4 a, mat4 b);
	friend vec4 operator*(mat4 m, vec4 v);

	void transpose();
	static mat4 transpose(mat4 m);

	static mat4 translation(vec3 pos);
	static mat4 scale(vec3 scale);
	static mat4 rotation(vec3 axis, float angle);
	static mat4 rotation(vec3 euler_angles);
	static mat4 transform(vec3 scale, vec3 rotation_axis, float angle, vec3 translation);
	static mat4 transform(vec3 scale, vec3 euler_angles, vec3 translation);

	static mat4 ortho(float near, float far, float left, float right, float top, float bottom);
	static mat4 perspective(float fovy, float aspect_ratio, float near, float far);

	static mat4 lookat(vec3 pos, vec3 up, vec3 right, vec3 dir);
};
