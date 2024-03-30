#pragma once
#include "./types.hpp"

template<typename T, int SIZE>
T euclidean_norm(Vector<T,SIZE> a) {
	T acc{ };
	for (int i=0; i<a.size; i++) acc += (a.v[i] * a.v[i]);
	return (T)std::sqrt(acc);
}

template<typename T, int SIZE>
T norm_induced_metric(Vector<T,SIZE>& a, Vector<T,SIZE>& b) {
	return euclidean_norm(a - b);
}

template<class T, int ROWS, int COLS> class Matrix;

template<typename T, int SIZE>
class Vector {
private:

	// T (*norm)(Vector) = euclidean_norm;
	// T (*metric)(Vector&, Vector&) = norm_induced_metric;

public:
	int size = SIZE;
	T v[SIZE];

	Vector() = default;
	Vector(T);
	Vector(Vector&) = default;
	Vector(std::array<T, SIZE>);
	~Vector() = default;

	void operator=(Vector&);

	void with_norm( T(*)(Vector&) );
	void with_metric( T(*)(Vector&,Vector&) );


	// operators:
	
	friend Vector operator*(Vector<T,SIZE>&, T);
	friend Vector operator*(T, Vector<T,SIZE>&);
	void operator*=(T);

	friend Vector operator+(Vector<T,SIZE>&, Vector<T,SIZE>&);
	friend Vector operator-(Vector<T,SIZE>&);
	friend Vector operator-(Vector<T,SIZE>&, Vector<T,SIZE>&);
	void operator+=(Vector&);
	void operator-=(Vector&);


	// other operations

	static T dot(Vector&, Vector&);
	// static T cross(Vector&, Vector&);
	
	T magnitude();
	
	void normalize();
	static Vector normalize(Vector&);


	// type casts:

	Matrix<T, SIZE, 1> as_col();
	Matrix<T, 1, SIZE> as_row();
};


typedef Vector<float,2> vec2;
typedef Vector<float,3> vec3;
typedef Vector<float,4> vec4;




// ..:: implementations ::..

// constructors:

template<typename T, int SIZE>
Vector<T,SIZE>::Vector(T x) : v{x} {}

template<typename T, int SIZE>
Vector<T,SIZE>::Vector(std::array<T, SIZE> a) {
	for (int i=0; i<SIZE; i++) v[i] = a[i];
}

template<typename T, int SIZE>
Matrix<T, SIZE, 1> Vector<T,SIZE>::as_col() {
	Matrix<T, SIZE, 1> res{};
	for (int i=0; i<size; i++) {
		res.m[i] = v[i];
	}
	return res;
}

template<typename T, int SIZE>
Matrix<T, 1, SIZE> Vector<T,SIZE>::as_row() {
	Matrix<T, 1, SIZE> res{};
	for (int i=0; i<size; i++) {
		res.m[i] = v[i];
	}
	return res;
}
