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



struct BuilderConfig {
	std::string path = "";
	void (*build_func)(std::shared_ptr<Resource>) = nullptr;
};



class ResourceManager {
private:
	std::unordered_map<std::string, BuilderConfig> builders;
	std::unordered_map<std::string, std::shared_ptr<Resource>> resources;

public:
	ResourceManager()
		: builders(std::unordered_map<std::string, BuilderConfig>())
		, resources(std::unordered_map<std::string, std::shared_ptr<Resource>>())
	{}
	~ResourceManager();

	bool register_resource(const std::string& key, const std::string& path);
	bool register_resource(const std::string& key, void (*build_func)(std::shared_ptr<Resource>));
	template<typename R> std::shared_ptr<R> get_resource(const std::string& key);
};



template<typename R>
std::shared_ptr<R> ResourceManager::get_resource(const std::string &key) {
	auto it = this->resources.find(key);
	if (it != this->resources.end()) {
		return std::dynamic_pointer_cast<R>(it->second);
	} else {
		std::shared_ptr<R> loaded_res = std::make_shared<R>();
		auto builder_it = this->builders.find(key);
		if (builder_it != this->builders.end()) {
			if (!builder_it->second.path.empty()) {
				loaded_res->load_from_file(builder_it->second.path);
			} else {
				// loaded_res = std::dynamic_pointer_cast<R>(builder_it->second.build_func());
				builder_it->second.build_func(loaded_res);
			}
			this->resources[key] = loaded_res;
			return loaded_res;
		} else {
			return std::shared_ptr<R>(nullptr);
		}
	}
}
