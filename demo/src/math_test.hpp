#pragma once

#include "math/types.hpp"
#include <array>
#include <iostream>

void math_test() {
	mat4 a(std::array<float,16>{
		1.0, 0.0, 2.0, 5.0,
		0.0, 1.0, 0.0, 0.0,
		7.0, 0.0, 1.0, 0.0,
		9.0, 0.0, 0.0, 1.0f
	});

	mat4 b(std::array<float,16>{
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0f
	});

	std::cout << "a\trows: " << a.rows << ", cols: " << a.cols << std::endl;
	std::cout << "b\trows: " << b.rows << ", cols: " << b.cols << std::endl;

	Matrix<float> res = a + b;
	mat4 res4 = res;
	std::cout << res4;

	std::cout << (a + Matrix<float>::transpose(a));
	std::cout << (a + Matrix<float>::transpose(a)).col(2).as_col();
}
