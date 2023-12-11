#include "core/say.hpp"
#include <iostream>

void Msg::say() {
	std::cout << this->msg << std::endl;
}
