#pragma once

#include <string>
#include <unordered_map>
#include <memory>


/* Provide default filepaths/resources under the keys:
 *   default_light_prop
 *   default_shader
 *   default_texture
 * */


class Resource {
public:
	Resource() = default;
	virtual ~Resource() = default;
	virtual void load_from_file(std::string& path) = 0;
};



class ResourceManager {
private:
	std::unordered_map<std::string, std::string> paths;
	std::unordered_map<std::string, std::shared_ptr<Resource>> resources;

public:
	ResourceManager()
		: paths(std::unordered_map<std::string, std::string>())
		, resources(std::unordered_map<std::string, std::shared_ptr<Resource>>())
	{}
	~ResourceManager();

	bool register_resource(const std::string& key, const std::string& path);
	template<typename R> std::shared_ptr<R> get_resource(const std::string& key);
};



template<typename R>
std::shared_ptr<R> ResourceManager::get_resource(const std::string &key) {
	// static_assert(!std::is_abstract_v<R>, "nope");

	auto it = this->resources.find(key);
	if (it != this->resources.end()) {
		return std::dynamic_pointer_cast<R>(it->second);
	} else {
		std::shared_ptr<R> loaded_res = std::make_shared<R>();
		auto path_it = this->paths.find(key);
		if (path_it != this->paths.end()) {
			loaded_res->load_from_file(path_it->second);
			this->resources[key] = loaded_res;
			return loaded_res;
		} else {
			return std::shared_ptr<R>(nullptr);
		}
	}
}
