#pragma once

#include <exception>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <memory>

#include <iostream>



// template<typename T>
// class Resource {
// private:
// 	T res;
// 
// public:
// 	Resource() = default;
// 	template<> static void load_from_file<T>(std::string& path);
// };



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

	/* loads the resource path into paths{key,path}.
	 * If the key already exists returns false, otherwise returns true
	 * and loads the path.
	 * */
	bool register_resource(const std::string& key, const std::string& path);

	/* the core module will need a pointer to the actual resource.
	 * The Resource class is only an abstraction to make the RM more flexible
	 * */
	template<typename R> std::shared_ptr<R> get_resource(const std::string& key);
	// std::shared_ptr<Resource> get_resource(const std::string& key);
	// template<typename R> std::shared_ptr<R> load_resource(const std::string& path);
	
	template<typename R> std::shared_ptr<R> create_resource();

private:
	template<typename R, typename = std::enable_if<!std::is_abstract_v<R>>>
	struct ResourceEnforcer : public R {};
};



template<typename R>
std::shared_ptr<R> ResourceManager::create_resource() {
	R res{};
	auto loaded_res = std::make_shared<R>(res);
	return loaded_res;
}



template<typename R>
std::shared_ptr<R> ResourceManager::get_resource(const std::string &key) {
	static_assert(!std::is_abstract_v<R>, "nope");

	auto it = this->resources.find(key);
	if (it != this->resources.end()) {
		std::cout << "already loaded" << std::endl;
		return std::dynamic_pointer_cast<R>(it->second);
	} else {
		std::cout << "loading..." << std::endl;
		R loaded_res{};
		// auto loaded_res = this->create_resource<R>();
		// auto loaded_res = std::make_shared<ResourceEnforcer<R>>();
		std::cout << "do you at least get to this point?" << std::endl; // the answer is no
		try {
			loaded_res.load_from_file(this->paths[it->first]);
			// this->resources[key] = std::dynamic_pointer_cast<R>(loaded_res);
			this->resources[key] = std::make_shared<R>(loaded_res);
			std::cout << "returning loaded resource" << std::endl;
			return std::dynamic_pointer_cast<R>(this->resources[key]);
		} catch(std::exception&) { // unregistered resource R
			std::cout << "fuck you" << std::endl;
			return std::shared_ptr<R>(nullptr);
		}
	}
}

// template<typename R>
// std::shared_ptr<R> ResourceManager::get_resource(const std::string &key) {
// 	auto it = this->resources.find(key);
// 	if (it != this->resources.end()) {
// 		std::cout << "already loaded" << std::endl;
// 		return std::dynamic_pointer_cast<R>(it->second);
// 	} else {
// 		auto loaded_res = std::make_shared<R>(new R());
// 		try {
// 
// 		} catch(std::exception&) { // unregistered resource
// 		}
// 	}
// }
