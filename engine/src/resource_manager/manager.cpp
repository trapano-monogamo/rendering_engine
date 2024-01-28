#include "resource_manager/manager.hpp"
#include <memory>

ResourceManager::~ResourceManager() {}

bool ResourceManager::register_resource(const std::string& key, const std::string& path) {
	if (this->paths.find(key) != this->paths.end()) { return false; }
	else {
		this->paths[key] = path;
		return true;
	}
}

template<typename R>
std::shared_ptr<R> ResourceManager::load_resource(const std::string&) { }
