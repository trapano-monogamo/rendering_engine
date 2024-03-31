#pragma once
#include "./types.hpp"

template<class T>
T euclidean_norm(Vector<T> a) {
	T acc{ };
	for (int i=0; i<a.size; i++) acc += (a.v[i] * a.v[i]);
	return (T)std::sqrt(acc);
}

template<class T>
T norm_induced_metric(Vector<T>& a, Vector<T>& b) {
	return euclidean_norm(a - b);
}

template<class T>
class Vector {
private:

	// T (*norm)(Vector) = euclidean_norm;
	// T (*metric)(Vector&, Vector&) = norm_induced_metric;

public:
	int size;
	T* v;

	Vector(int size);
	Vector(int size, T value);
	Vector(int size, T* values);
	Vector(Vector&);
	~Vector() = default;

	void operator=(Vector&);

	void with_norm( T(*)(Vector&) );
	void with_metric( T(*)(Vector&,Vector&) );


	// operators:
	
	template<class _T> friend Vector operator*(Vector&, T);
	template<class _T> friend Vector operator*(T, Vector&);
	void operator*=(T);

	template<class _T> friend Vector operator+(Vector&, Vector&);
	template<class _T> friend Vector operator-(Vector&);
	template<class _T> friend Vector operator-(Vector&, Vector&);
	void operator+=(Vector&);
	void operator-=(Vector&);


	// other operations

	static T dot(Vector&, Vector&);
	// static T cross(Vector&, Vector&);

	T magnitude();

	void normalize();
	static Vector normalize(Vector&);


	// type casts:

	Matrix<T> as_col();
	Matrix<T> as_row();
};


// typedef Vector<float,2> vec2;
// typedef Vector<float,3> vec3;
// typedef Vector<float,4> vec4;




// ..:: implementations ::..

// constructors:

template<class T> Vector<T>::Vector(int size)
	: size(size)
{
	v = new T[size]();
}

template<class T> Vector<T>::Vector(int size, T x)
	: size(size)
{
	v = new T[size];
	for (int i=0; i<size; i++) v[i] = x;
}

template<class T> Vector<T>::Vector(int size, T* values)
	: size(size)
{
	v = new T[size];
	for (int i=0; i<size; i++) v[i] = values[i];
}

template<class T> Matrix<T> Vector<T>::as_col() {
	Matrix<T> res(size, 1);
	for (int i=0; i<size; i++) res.m[i] = v[i];
	return res;
}

template<class T> Matrix<T> Vector<T>::as_row() {
	Matrix<T> res(1, size);
	for (int i=0; i<size; i++) res.m[i] = v[i];
	return res;
}
