#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>



class System {
public:
	virtual ~System() = default;
	virtual void update() = 0; // must override
};



struct Component {
	Component() = default;
	virtual ~Component() = default;
};



class ECS;
struct Query {
	std::vector<uint32_t> results;
	template<typename T> Query& with_component(ECS* const ecs);
};



class ECS {
public:
	std::vector<uint32_t> entities;
	std::unordered_map<uint32_t, std::vector<std::shared_ptr<Component>>> components; // <---- change to shared ptr
	std::vector<std::shared_ptr<System>> systems;

	ECS() = default;
	~ECS();

	void update();

	uint32_t add_entity();
	void remove_entity(uint32_t entity);
	template<typename T> void add_component(uint32_t entity, T* component);
	template<typename T> void add_component(uint32_t entity, T component);
	template<typename T> void add_component(uint32_t entity, std::shared_ptr<T> component);
	template<typename T> void remove_component(uint32_t entity);
	void add_system(System* sys);
	void add_system(std::shared_ptr<System>);
	void remove_system(System* sys);

	template<typename T> std::shared_ptr<T> get_system();

	template<typename T> std::shared_ptr<T> get_component(uint32_t entity);
	template<typename T> std::vector<std::shared_ptr<T>> query_components();
	template<typename T> bool has_component(uint32_t entity);

	Query query_entities();
};



template<typename T>
Query& Query::with_component(ECS * const ecs) {
	std::vector<uint32_t> temp_res{ };

	for (auto& entity : this->results)
		if (ecs->has_component<T>(entity))
			temp_res.push_back(entity);

	this->results.clear();
	this->results = temp_res;

	return *this;
}



template<typename T>
void ECS::add_component(uint32_t entity, T* component) {
	auto it = this->components.find(entity);
	// if the map already has the key, add the component to its value
	if (it != this->components.end())
		it->second.push_back(std::make_shared<T>(*component));
	else
		this->components.insert(std::make_pair(entity, std::vector<std::shared_ptr<Component>>{std::make_shared<T>(*component)}));
}

template<typename T>
void ECS::add_component(uint32_t entity, std::shared_ptr<T> component) {
	auto it = this->components.find(entity);
	// if the map already has the key, add the component to its value
	if (it != this->components.end())
		it->second.push_back(component);
	else
		this->components.insert(std::make_pair(entity, std::vector<std::shared_ptr<Component>>{component}));
}

template<typename T>
void ECS::add_component(uint32_t entity, T component) {
//	auto c = std::move(component);
	auto it = this->components.find(entity);
	// if the map already has the key, add the component to its value
	if (it != this->components.end())
		it->second.push_back(std::make_shared<T>(component));
	else
		this->components.insert(std::make_pair(entity, std::vector<std::shared_ptr<Component>>{std::make_shared<T>(component)}));
}

template<typename T>
std::shared_ptr<T> ECS::get_component(uint32_t entity) {
	auto it = this->components.find(entity);
	if (it != this->components.end()) {
		for (std::shared_ptr<Component>& comp : it->second) {
			// T* res = dynamic_cast<T*>(comp);
			std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(comp);
			if (res.get() != nullptr) {
				return res;
			}
		}
	}
	return std::shared_ptr<T>(nullptr);
}

template<typename T>
std::vector<std::shared_ptr<T>> ECS::query_components() {
	std::vector<std::shared_ptr<T>> res{ };
	for (auto entry : this->components) {
		for (std::shared_ptr<Component>& c : entry.second) {
			T* tc = std::dynamic_pointer_cast<T>(c);
			if (tc != nullptr) res.push_back(tc);
		}
	}
	return res;
}

template<typename T>
bool ECS::has_component(uint32_t entity) {
	if (this->get_component<T>(entity) != nullptr) return true;
	else return false;
}

template<typename T>
std::shared_ptr<T> ECS::get_system() {
	for (std::shared_ptr<System>& sys : this->systems) {
		std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(sys);
		if (res != nullptr) {
			return res;
		}
	}
	return nullptr;
}
