#include "resource_manager/resource_manager.hpp"
#include <memory>

ResourceManager::~ResourceManager() {
	for (auto& builder : builders) {
		delete static_cast<BuilderFunctionWrapper<Resource>*>(builder.second.bfw);
	}
}

void ResourceManager::register_resource(const std::string& key, const std::string& path) {
	if (this->builders.find(key) != this->builders.end()) { return; }
	else {
		// this->builders[key] = { .path = path, .bfw = nullptr };
		this->builders[key] = BuilderConfig( path, nullptr);
		return;
	}
}

bool ResourceManager::is_resource_registered(const std::string& key) {
	return (this->builders.find(key) != this->builders.end());
}
