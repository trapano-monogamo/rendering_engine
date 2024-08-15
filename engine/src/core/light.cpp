#include "core/light.hpp"

Light::Light(vec3 pos, vec3 ambient, vec3 diffuse, vec3 specular, vec3 color)
	: pos(pos)
	, ambient(ambient)
	, diffuse(diffuse)
	, specular(specular)
	, color(color)
{}
