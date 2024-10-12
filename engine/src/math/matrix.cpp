#include "math/matrix.hpp"


/* MATRIX IMPLEMENTATION */

Matrix::Matrix(unsigned int r, unsigned int c)
	: r(r), c(c)
{
	m = new float[r*c];
	for (unsigned int i=0; i<r*c; i++) m[i] = 0.f;
}

Matrix::Matrix(unsigned int r, unsigned int c, std::vector<float>&& arr)
	: r(r), c(c)
{
	m = new float[r*c];
	for (unsigned int i=0; i<r*c; i++) m[i] = arr[i];
}

Matrix::Matrix(Matrix&& a) {
	m = new float[a.rows() * a.cols()];
	for(unsigned int i=0; i<a.rows() * a.cols(); i++) m[i] = a[i];
}

Matrix::~Matrix() {
	r = 0;
	c = 0;
	delete[] m;
	m = nullptr;
}

unsigned int Matrix::rows() const { return r; }
unsigned int Matrix::cols() const { return c; }

float Matrix::operator[](unsigned int idx) const {
	if (idx >= r*c) throw OutOfRangeIndex;
	else return m[idx];
}

Vector Matrix::col(unsigned int j) const {
	Vector v(r);
	for (unsigned int k=0; k<r; k++) v.at(k) = this->get(k,j);
	return v;
}

Covector Matrix::row(unsigned int i) const {
	Covector v(c);
	for (unsigned int k=0; k<c; k++) v.at(k) = this->get(i,k);
	return v;
}

float& Matrix::at(unsigned int i, unsigned int j) {
	if (i >= r || j >= c) throw OutOfRangeIndex;
	else return m[i * c + j];
}

float& Matrix::at(unsigned int i) {
	if (i >= r*c) throw OutOfRangeIndex;
	else return m[i];
}

float Matrix::get(unsigned int i, unsigned int j) const {
	if (i >= r || j >= c) throw OutOfRangeIndex;
	else return m[i * c + j];
}

float Matrix::get(unsigned int i) const {
	if (i >= r*c) throw OutOfRangeIndex;
	else return m[i];
}

Matrix Matrix::transpose() const {
	Matrix res(c,r);
	for (unsigned int i=0; i<c; i++)
		for (unsigned int j=0; j<r; j++)
			res.at(i,j) = get(j,i);
	return res;
}

void Matrix::operator=(const Matrix& a) {
	if (r != a.rows() || c != a.cols()) throw InvalidMatrixSize;
	if (m) delete[] m;
	m = new float[r*c];
	for (unsigned int i=0; i<r*c; i++) m[i] = a[i];
}

Matrix operator+(const Matrix& a, const Matrix& b) {
	if (a.rows() != b.rows() || a.cols() != b.cols()) throw InvalidMatrixSize;
	Matrix res(a.rows(), a.cols());
	for (unsigned int i=0; i<res.rows() * res.cols(); i++) res.at(i) = a[i] + b[i];
	return res;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
	if (a.rows() != b.rows() || a.cols() != b.cols()) throw InvalidMatrixSize;
	Matrix res(a.rows(), a.cols());
	for (unsigned int i=0; i<res.rows() * res.cols(); i++) res.at(i) = a[i] - b[i];
	return res;
}

Matrix Matrix::operator-() const {
	Matrix res(r,c);
	for (unsigned int i=0; i<r*c; i++) res.at(i) = m[i] * -1.f;
	return res;
}

void Matrix::operator+=(const Matrix& a) {
	if (a.rows() != r || a.cols() != c) throw InvalidMatrixSize;
	for (unsigned int i=0; i<r*c; i++) m[i] += a[i];
}

void Matrix::operator-=(const Matrix& a) {
	if (a.rows() != r || a.cols() != c) throw InvalidMatrixSize;
	for (unsigned int i=0; i<r*c; i++) m[i] -= a[i];
}

Matrix operator*(const Matrix& a, const Matrix& b) {
	Matrix res(a.rows(), b.cols());
	for (unsigned int i=0; i<a.rows(); i++)
		for (unsigned int j=0; j<b.cols(); j++)
			for (unsigned int k=0; k<a.cols(); k++)
				res.at(i,j) += a.get(i,k) * b.get(k,j);
	return res;
}

Matrix operator*(float x, const Matrix& a) {
	Matrix res(a.rows(), a.cols());
	for (unsigned int i=0; i<a.rows()*a.cols(); i++) res.at(i) = a[i] * x;
	return res;
}
