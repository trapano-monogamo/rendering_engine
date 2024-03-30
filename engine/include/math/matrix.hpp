#pragma once
#include "./types.hpp"
#include <array>
#include <ostream>
#include <stdexcept>

template<typename T, int SIZE> class Vector;

template<class T, int ROWS, int COLS>
class Matrix {
public:
	int rows = ROWS;
	int cols = COLS;
	T m[ROWS * COLS];

public:
	Matrix() = default;
	Matrix(T);
	Matrix(Matrix&) = default;
	Matrix(std::array<T, ROWS * COLS>);
	~Matrix() = default;

	void operator=(Matrix&);


	// basic functionalities:

	Vector<T, COLS> row(int r);
	Vector<T, ROWS> col(int c);

	void transpose();
	static Matrix<T, COLS, ROWS> transpose(Matrix&);


	// operators:

	friend Matrix operator*(Matrix&, T);
	friend Matrix operator*(T, Matrix&);
	void operator*=(T);

	friend Matrix operator+(Matrix&, Matrix&);
	friend Matrix operator-(Matrix&);
	friend Matrix operator-(Matrix&, Matrix&);
	void operator+=(Matrix&);
	void operator-=(Matrix&);

	friend Matrix operator*(Matrix&, Matrix&);
	void operator*=(Matrix&);

	friend std::ostream& operator<<(std::ostream& out, Matrix a) {
		out << "{ ";
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


typedef Matrix<float,2,2> mat2;
typedef Matrix<float,3,3> mat3;
typedef Matrix<float,4,4> mat4;



// ..:: implementations ::..

// constructors

template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS>::Matrix(T x) : m{x} {}

template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS>::Matrix(std::array<T, ROWS*COLS> a) {
	for (int i=0; i<ROWS*COLS; i++) m[i] = a[i];
}

template<typename T, int ROWS, int COLS>
void Matrix<T,ROWS,COLS>::operator=(Matrix& a) {
	if (rows != a.rows || cols != a.cols)
		throw std::invalid_argument("Matrices of incompatible size.");
	else
		for (int i=0; i<rows*cols; i++) m[i] = a[i];
}


// basic functionality

template<typename T, int ROWS, int COLS>
Vector<T, COLS> Matrix<T,ROWS,COLS>::row(int r) {
	Vector<T,COLS> v{};
	for (int i=0; i<COLS; i++)
		v.v[i] = m[r * cols + i];
	return v;
}

template<typename T, int ROWS, int COLS>
Vector<T, ROWS> Matrix<T,ROWS,COLS>::col(int c) {
	Vector<T,ROWS> v{};
	for (int i=0; i<ROWS; i++)
		v.v[i] = m[i * cols + c];
	return v;
}

template<typename T, int ROWS, int COLS>
void transpose();

template<typename T, int ROWS, int COLS>
Matrix<T, COLS, ROWS> Matrix<T, ROWS, COLS>::transpose(Matrix& a) {
	Matrix<T, COLS, ROWS> res{};
	for (int r=0; r<a.rows; r++) {
		for (int c=0; c<a.cols; c++) {
			res.m[c * res.cols + r] = a.m[r * a.cols + c];
		}
	}
	return res;
}


// operators

template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS> operator*(Matrix<T,ROWS,COLS>& a, T x) {
	Matrix<T,ROWS,COLS> res{};
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] * x;
	return res;
}

template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS> operator*(T x, Matrix<T,ROWS,COLS>& a) {
	Matrix<T,ROWS,COLS> res{};
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] * x;
	return res;
}

template<typename T, int ROWS, int COLS>
void Matrix<T,ROWS,COLS>::operator*=(T x) {
	for (int i=0; i<rows*cols; i++)
		m[i] *= x;
}


template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS> operator+(Matrix<T,ROWS,COLS>& a, Matrix<T,ROWS,COLS>& b) {
	Matrix<T,ROWS,COLS> res{};
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] + b.m[i];
	return res;
}

template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS> operator-(Matrix<T,ROWS,COLS>& a) {
	Matrix<T,ROWS,COLS> res{};
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = -a.m[i];
	return res;
}

template<typename T, int ROWS, int COLS>
Matrix<T,ROWS,COLS> operator-(Matrix<T,ROWS,COLS>& a, Matrix<T,ROWS,COLS>& b) {
	Matrix<T,ROWS,COLS> res{};
	for (int i=0; i<res.rows*res.cols; i++)
		res.m[i] = a.m[i] - b.m[i];
	return res;
}

template<typename T, int ROWS, int COLS>
void Matrix<T,ROWS,COLS>::operator+=(Matrix& a) {
	for (int i=0; i<rows*cols; i++)
		m[i] += a.m[i];
}

template<typename T, int ROWS, int COLS>
void Matrix<T,ROWS,COLS>::operator-=(Matrix& a) {
	for (int i=0; i<rows*cols; i++)
		m[i] -= a.m[i];
}


template<typename T, int ROWS_A, int COLS_A, int ROWS_B, int COLS_B>
Matrix<T,ROWS_A,COLS_B> operator*(Matrix<T,ROWS_A,COLS_A>& a, Matrix<T,ROWS_B,COLS_B>& b) {
	if (COLS_A != ROWS_B)
		throw std::invalid_argument("Matrices of incompatible size.");

	Matrix<T,ROWS_A,COLS_B> res{};
	for (int r=0; r<res.rows; r++) {
		for (int c=0; c<res.cols; c++) {
			T acc{};
			for (int k=0; k<COLS_A; k++) {
				acc += a.m[ r * a.cols + k ] * b.m[ k * b.cols + c ];
			}
			res[ r * res.rows + c ] = acc;
		}
	}

	return res;
}

template<typename T, int ROWS, int COLS>
void Matrix<T,ROWS,COLS>::operator*=(Matrix& a) {
	*this = (*this * a);
}
