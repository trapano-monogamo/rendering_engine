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
	std::unordered_map<uint32_t, std::vector<Component*>> components;
	std::vector<System*> systems;

	ECS() = default;
	~ECS();

	void update();

	uint32_t add_entity();
	void remove_entity(uint32_t entity);
	template<typename T> void add_component(uint32_t entity, T* component);
	template<typename T> void remove_component(uint32_t entity);
	void add_system(System* sys);
	void remove_system(System* sys);

	template<typename T> T* get_system();

	template<typename T> T* get_component(uint32_t entity);
	template<typename T> std::vector<T*> query_components();
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
		it->second.push_back(component);
	else
		this->components.insert(std::make_pair(entity, std::vector<Component*>{component}));
}

template<typename T>
T* ECS::get_component(uint32_t entity) {
	auto it = this->components.find(entity);
	if (it != this->components.end()) {
		for (Component*& comp : it->second) {
			T* res = dynamic_cast<T*>(comp);
			if (res != nullptr) {
				return res;
			}
		}
	}
	return nullptr;
}

template<typename T>
std::vector<T*> ECS::query_components() {
	std::vector<T*> res{ };
	for (auto entry : this->components) {
		for (Component*& c : entry.second) {
			T* tc = dynamic_cast<T*>(c);
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
T* ECS::get_system() {
	for (System*& sys : this->systems) {
		T* res = dynamic_cast<T*>(sys);
		if (res != nullptr) {
			return res;
		}
	}
	return nullptr;
}
