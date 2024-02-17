#include "core/material.hpp"

LightProperties::LightProperties(float s, vec3 a, vec3 d, vec3 r)
	: shininess(s)
	, ambient(a)
	, diffuse(d)
	, reflective(r)
{}

// void LightProperties::load_from_file(std::string& path) { }
