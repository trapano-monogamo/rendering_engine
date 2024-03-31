#pragma once
#include "./types.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

struct mat4;

template<class T> class Matrix {
public:
	int rows;
	int cols;
	T* m;

public:
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, const T& value);
	Matrix(int rows, int cols, const T* values);
	Matrix(const Matrix& m);
	virtual ~Matrix();

	void operator=(const Matrix&);
	operator mat4();


	// basic functionalities:
	
	T& at(int r, int c);

	Vector<T> row(int r);
	Vector<T> col(int c);

	void transpose();
	static Matrix transpose(const Matrix&);


	// operators:

	template<class _T> friend Matrix operator*(const Matrix&, const T&);
	template<class _T> friend Matrix operator*(const T&, const Matrix&);
	void operator*=(const T&);

	template<class _T> friend Matrix operator+(const Matrix&, const Matrix&);
	template<class _T> friend Matrix operator-(const Matrix&);
	template<class _T> friend Matrix operator-(const Matrix&, const Matrix&);
	void operator+=(const Matrix&);
	void operator-=(const Matrix&);

	template<class _T> friend Matrix operator*(const Matrix&, const Matrix&);
	void operator*=(const Matrix&);

	friend std::ostream& operator<<(std::ostream& out, Matrix a) {
		out << std::endl << "{ ";
		for (int r=0; r<a.rows; r++) {
			for (int c=0; c<a.cols; c++) {
				out << a.m[r * a.cols + c] << ", ";
			}
			if (r != a.rows - 1) out << std::endl << "  ";
			else out << "}" << std::endl;
		}
		return out;
	}


	// other operations:

	// template<std::enable_if<ROWS == COLS>> T determinant();
};


struct mat4 : public Matrix<float> {
	mat4() : Matrix<float>(4,4) {}
	mat4(float x) : Matrix<float>(4,4,x) {}
	mat4(const std::array<float, 16>& values) : Matrix<float>(4,4,values.data()) {}
};

// typedef Matrix<float,2,2> mat2;
// typedef Matrix<float,3,3> mat3;
// typedef Matrix<float,4,4> mat4;



// ..:: implementations ::..

// constructors and destructor

template<class T> Matrix<T>::Matrix(int rows, int cols)
	: rows(rows)
	, cols(cols)
{
	m = new T[rows * cols]();
}

template<class T> Matrix<T>::Matrix(int rows, int cols, const T& x)
	: rows(rows)
	, cols(cols)
{
	m = new T[rows * cols];
	for (int i=0; i<rows*cols; i++) m[i] = x;
}

template<class T> Matrix<T>::Matrix(int rows, int cols, const T* a)
	: rows(rows)
	, cols(cols)
{
	m = new T[rows * cols];
	for (int i=0; i<rows*cols; i++) m[i] = a[i];
}

template<class T> Matrix<T>::Matrix(const Matrix& a)
	: rows(a.rows)
	, cols(a.cols)
{
	m = new T[rows * cols];
	for (int i=0; i<rows*cols; i++) m[i] = a.m[i];
}

template<class T> Matrix<T>::~Matrix() {
	delete[] m;
}

template<class T> void Matrix<T>::operator=(const Matrix& a) {
	rows = a.rows;
	cols = a.cols;
	delete[] m;
	m = new T[rows * cols];
	for (int i=0; i<rows*cols; i++) m[i] = a[i];
}

// WHY DO YOU HAVE TO BE SO BITCHY, C++... HUH???? JUST DO WHAT I ASK YOU TO DO FOR FUCK'S SAKE
template<class T> Matrix<T>::operator mat4() {
	mat4* res = dynamic_cast<mat4*>(this);
	if (res != nullptr) {
		return *res;
	} else {
		throw std::invalid_argument("Could not cast 'Matrix<float>' to 'mat4'.");
	}
}


// basic functionality

template<class T> T& Matrix<T>::at(int r, int c) {
	return m[r * cols + c];
}

template<class T> Vector<T> Matrix<T>::row(int r) {
	Vector<T> v(cols);
	for (int i=0; i<cols; i++)
		v.v[i] = m[r * cols + i];
	return v;
}

template<class T> Vector<T> Matrix<T>::col(int c) {
	Vector<T> v(rows);
	for (int i=0; i<rows; i++)
		v.v[i] = m[i * cols + c];
	return v;
}

template<class T> void transpose();

template<class T> Matrix<T> Matrix<T>::transpose(const Matrix& a) {
	Matrix<T> res(a.cols, a.rows);
	for (int r=0; r<a.rows; r++) {
		for (int c=0; c<a.cols; c++) {
			res.m[c * res.cols + r] = a.m[r * a.cols + c];
		}
	}
	return res;
}


// operators

template<class T> Matrix<T> operator*(const Matrix<T>& a, const T& x) {
	Matrix<T> res(a.rows, a.cols);
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] * x;
	return res;
}

template<class T> Matrix<T> operator*(const T& x, const Matrix<T>& a) {
	Matrix<T> res(a.rows,a.cols);
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] * x;
	return res;
}

template<class T> void Matrix<T>::operator*=(const T& x) {
	for (int i=0; i<rows*cols; i++) m[i] *= x;
}


template<class T> Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b) {
	if (!(a.rows == b.rows && a.cols == b.cols)) {
		throw std::invalid_argument("Matrices of incompatible types.");
	}
	Matrix<T> res(a.rows,a.cols);
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] + b.m[i];
	return res;
}

template<class T> Matrix<T> operator-(const Matrix<T>& a) {
	Matrix<T> res(a.rows,a.cols);
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = -a.m[i];
	return res;
}

template<class T> Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b) {
	if (!(a.rows == b.rows && a.cols == b.cols)) {
		throw std::invalid_argument("Matrices of incompatible types.");
	}
	Matrix<T> res(a.rows, a.cols);
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] - b.m[i];
	return res;
}

template<class T> void Matrix<T>::operator+=(const Matrix& a) {
	for (int i=0; i<rows*cols; i++) m[i] += a.m[i];
}

template<class T> void Matrix<T>::operator-=(const Matrix& a) {
	for (int i=0; i<rows*cols; i++) m[i] -= a.m[i];
}


template<class T> Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) {
	if (a.cols != b.rows) {
		throw std::invalid_argument("Matrices of incompatible size.");
	}

	Matrix<T> res(a.rows,b.cols);
	for (int r=0; r<res.rows; r++) {
		for (int c=0; c<res.cols; c++) {
			T acc{};
			for (int k=0; k<a.cols; k++) {
				acc += a.m[ r * a.cols + k ] * b.m[ k * b.cols + c ];
			}
			res.m[ r * res.rows + c ] = acc;
		}
	}

	return res;
}

template<class T> void Matrix<T>::operator*=(const Matrix& a) {
	*this = (*this * a);
}
