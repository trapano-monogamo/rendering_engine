#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>

struct Entity { uint32_t id; };

struct Component {
	Component() = default;
	virtual ~Component() = default;
};

class ECS {
public:
	std::vector<Entity> entities;
	std::unordered_map<uint32_t, std::vector<Component*>> components;
	std::vector<void (*)(ECS&)> systems;

	ECS() = default;
	~ECS();

	void update();

	void add_entity(uint32_t entity);
	void remove_entity(uint32_t entity);
	template<typename T> void add_component(uint32_t entity, T* component);
	template<typename T> void remove_component(uint32_t entity);
	void add_system(void (*sys)(ECS&));
	void remove_system(void (*sys)(ECS&));

	template<typename T> T* get_component(uint32_t entity);
	template<typename T> std::vector<T*> query_components();
};

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
			if (res != nullptr) { return res; }
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
