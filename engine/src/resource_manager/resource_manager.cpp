#include "resource_manager/resource_manager.hpp"
#include <memory>

ResourceManager::~ResourceManager() {}

bool ResourceManager::register_resource(const std::string& key, const std::string& path) {
	if (this->builders.find(key) != this->builders.end()) { return false; }
	else {
		this->builders[key] = { .path = path, .build_func = nullptr };
		return true;
	}
}

bool ResourceManager::register_resource(const std::string& key, void (*build_func)(std::shared_ptr<Resource>)) {
	if (this->builders.find(key) != this->builders.end()) { return false; }
	else {
		this->builders[key] = { .path = "", .build_func = build_func };
		return true;
	}
}
