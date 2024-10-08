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
	virtual void load_from_file(const std::string&) = 0;
};



template<typename R>
struct ResourceConfig {
	std::string key = "";
	std::string path = "";
	std::shared_ptr<R> (* func)() = nullptr;

	ResourceConfig() = default;
	ResourceConfig(const std::string& key) : key(key) {}
	ResourceConfig(const std::string& key, const std::string& path) : key(key), path(path) {}
	ResourceConfig(const std::string& key, std::shared_ptr<R> (*func)()) : key(key), func(func) {}
};



class ResourceManager {
private:
	template<class R>
	struct BuilderFunctionWrapper {
		std::shared_ptr<R> (*build_func)() = nullptr;

		BuilderFunctionWrapper(std::shared_ptr<R> (*build_func)())
			: build_func(build_func) {}
	};

	struct BuilderConfig {
		// could this be a union to make it clear that it's either one or the other? Is there a similar solution?
		std::string path = "";
		void* bfw = nullptr;

		BuilderConfig() = default;
		BuilderConfig(std::string path, void* bfw)
			: path(path), bfw(bfw) {}
	};

private:
	std::unordered_map<std::string, BuilderConfig> builders;
	std::unordered_map<std::string, std::shared_ptr<Resource>> resources;

public:
	ResourceManager()
		: builders(std::unordered_map<std::string, BuilderConfig>())
		, resources(std::unordered_map<std::string, std::shared_ptr<Resource>>())
	{}
	~ResourceManager();

	bool is_resource_registered(const std::string& key);
	void register_resource(const std::string& key, const std::string& path);
	template<typename R> void register_resource(const std::string& key, std::shared_ptr<R> (*build_func)());
	template<typename R> void register_resource(ResourceConfig<R> config);
	template<typename R> std::shared_ptr<R> get_resource(const std::string& key);
};

template<typename R>
void ResourceManager::register_resource(const std::string& key, std::shared_ptr<R> (*build_func)()) {
	if (this->builders.find(key) != this->builders.end()) { return; }
	else {
		this->builders[key] = BuilderConfig("", new BuilderFunctionWrapper<R>{ build_func });
		return;
	}
}

template<typename R>
void ResourceManager::register_resource(ResourceConfig<R> config) {
	if (config.path.empty()) // if no path => function
		this->register_resource(config.key, config.func);
	else // if no function => path
		this->register_resource(config.key, config.path);
}




template<typename R>
std::shared_ptr<R> ResourceManager::get_resource(const std::string &key) {
	auto it = this->resources.find(key);
	if (it != this->resources.end()) {
		return std::dynamic_pointer_cast<R>(it->second);
	} else {
		std::shared_ptr<R> loaded_res = std::make_shared<R>();
		auto builder_it = this->builders.find(key);
		if (builder_it != this->builders.end()) {
			if (builder_it->second.bfw != nullptr) {
				// loaded_res = std::dynamic_pointer_cast<R>(builder_it->second.build_func());
				// builder_it->second.build_func(loaded_res);
				loaded_res = std::dynamic_pointer_cast<R>(((BuilderFunctionWrapper<R>*)builder_it->second.bfw)->build_func());
			} else {
				loaded_res->load_from_file(builder_it->second.path);
			}
			this->resources[key] = loaded_res;
			return loaded_res;
		} else {
			return std::shared_ptr<R>(nullptr);
		}
	}
}
