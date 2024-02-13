#pragma once

#include <exception>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <memory>

#include <iostream>


class Resource {
public:
	Resource() = default;
	virtual ~Resource() = default;
	virtual void load_from_file(std::string& path) = 0;
};



class ResourceManager {
private:
	std::unordered_map<std::string, std::string> paths;
	std::unordered_map<std::string, Resource*> resources;

public:
	ResourceManager()
		: paths(std::unordered_map<std::string, std::string>())
		, resources(std::unordered_map<std::string, Resource*>())
	{}
	~ResourceManager();

	bool register_resource(const std::string& key, const std::string& path);
	template<typename R> R* get_resource(const std::string& key);
};



template<typename R>
R* ResourceManager::get_resource(const std::string &key) {
	auto it = this->resources.find(key);
	if (it != this->resources.end()) {
		std::cout << "already loaded" << std::endl;
		return (R*)(it->second);
	} else {
		std::cout << "loading..." << std::endl;
		R* loaded_res = new R; // <------ SEGFAULT
		std::cout << "loaded." << std::endl;
		try {
			loaded_res->load_from_file(this->paths[it->first]);
			this->resources[key] = loaded_res;
			std::cout << "returning loaded resource" << std::endl;
			return (R*)(this->resources[key]);
		} catch(std::exception&) { // unregistered resource R
			std::cout << "nope" << std::endl;
			return nullptr;
		}
	}
}

// template<typename R>
// const R& ResourceManager::get_resource(const std::string &key) {
// 	static_assert(!std::is_abstract_v<R>, "nope");
// 
// 	auto it = this->resources.find(key);
// 	if (it != this->resources.end()) {
// 		std::cout << "already loaded" << std::endl;
// 		return std::dynamic_pointer_cast<R>(it->second);
// 	} else {
// 		std::cout << "loading..." << std::endl;
// 		R loaded_res{};
// 		// auto loaded_res = this->create_resource<R>();
// 		// auto loaded_res = std::make_shared<ResourceEnforcer<R>>();
// 		std::cout << "do you at least get to this point?" << std::endl; // the answer is no
// 		try {
// 			loaded_res.load_from_file(this->paths[it->first]);
// 			// this->resources[key] = std::dynamic_pointer_cast<R>(loaded_res);
// 			this->resources[key] = std::make_shared<R>(loaded_res);
// 			std::cout << "returning loaded resource" << std::endl;
// 			return std::dynamic_pointer_cast<R>(this->resources[key]);
// 		} catch(std::exception&) { // unregistered resource R
// 			std::cout << "fuck you" << std::endl;
// 			return std::shared_ptr<R>(nullptr);
// 		}
// 	}
// }

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
