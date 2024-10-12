#pragma once

#include <vector>
#include <array>

class InvalidMatrixSize : public std::exception;
class OutOfRangeIndex : public std::exception;

class Vector;
class Covector;

class Matrix {
private:
	unsigned int r, c;
	float* m;

public:
	Matrix(unsigned int, unsigned int);
	Matrix(unsigned int, unsigned int, std::vector<float>&&);
	Matrix(Matrix&&);
	virtual ~Matrix();

	unsigned int rows() const;
	unsigned int cols() const;

	static Matrix identity(unsigned int);

	// std::enable_if the mrix is not Vector/Covector => if M != 1 || N != 1
	float& at(unsigned int, unsigned int);
	float get(unsigned int, unsigned int) const;

	// std::enable_if the mrix is Vector/Covector => if M == 1 || N == 1
	float& at(unsigned int);
	float get(unsigned int) const;

	float operator[](unsigned int) const;

	Vector col(unsigned int j = 0) const;
	Covector row(unsigned int i = 0) const;

	Matrix transpose() const;

	void operator=(const Matrix&);
	
	friend Matrix<_M,_N> operator+(const Matrix&, const Matrix&);
	friend Matrix<_M,_N> operator-(const Matrix&, const Matrix&);
	Matrix operator-() const;
	void operator+=(const Matrix&);
	void operator-=(const Matrix&);

	friend Matrix operator*(const Matrix&, const Matrix&);
	friend Matrix operator*(float, const Matrix&);

	operator vec2() const;
	operator vec3() const;

	// (std::enable_if square matrix)
	//  1. identity
	//  2. determinant
	//  3. trace
	//  4. eigenvalues
};

struct Vector : public Matrix {
	Vector(unsigned int);
	Vector(std::vector<float>&&);
	Vector(Matrix&&);
};

struct Covector : public Matrix {
	Covector(unsigned int);
	Covector(std::vector<float>&&);
	Covector(Matrix&&);
};

template<unsigned int M, unsigned N>
class Mat : public Matrix {
	Mat() : Matrix(M,N) {}
	Mat(std::array<float, M*N>&& arr) : Matrix(M,N,arr) {}
};

template<unsigned int N>
class Vec : public Vector {}

template<unsigned int N>
class Dual : public Covector {}
