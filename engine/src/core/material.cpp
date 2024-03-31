#include "core/material.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

Material::Material(float sh, vec3 a, vec3 d, vec3 sp)
	: shininess(sh)
	, ambient(a)
	, diffuse(d)
	, specular(sp)
{}

// .mat
void Material::load_from_file(std::string& path) {
	std::ifstream f(path);
	if (!f.good()) {
		throw std::runtime_error("Could not open .mat file.");
		return;
	}

	std::string line;
	std::string attr;
	while (!f.eof()) {
		f >> attr;
		if (attr.find("ambient") != std::string::npos) {
			f >> ambient.x >> ambient.y >> ambient.z;
		} else if (attr.find("diffuse") != std::string::npos) {
			f >> diffuse.x >> diffuse.y >> diffuse.z;
		} else if (attr.find("specular") != std::string::npos) {
			f >> specular.x >> specular.y >> specular.z;
		} else if (attr.find("shininess") != std::string::npos) {
			f >> shininess;
		}
	}
}
