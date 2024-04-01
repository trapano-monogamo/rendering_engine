#include "resource_manager/resource_manager.hpp"
#include <memory>

ResourceManager::~ResourceManager() {}

bool ResourceManager::register_resource(const std::string& key, const std::string& path) {
	if (this->builders.find(key) != this->builders.end()) { return false; }
	else {
		this->builders[key] = { .path = path, .bfw = nullptr };
		return true;
	}
}
