#pragma once

#include <string>

struct Msg {
	std::string msg;

	Msg(const char* msg) : msg(msg) {}
	~Msg() = default;

	void say();
};
