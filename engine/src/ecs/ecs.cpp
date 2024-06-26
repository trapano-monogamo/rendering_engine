#include "ecs/ecs.hpp"
#include <algorithm>
#include <memory>

ECS::~ECS() {
	// ugly as hell solution to avoid deleting duplicate components
	std::vector<Component*> ptrs{};
	for (auto entry : this->components) {
		for (Component* c : entry.second) {
			if (std::find(ptrs.begin(), ptrs.end(), c) == ptrs.end()) ptrs.push_back(c);
		}
	}

	for (Component* c : ptrs) delete c;
	// for (auto sys : this->systems) delete sys;
}

void ECS::update() {
	for (auto system : this->systems) {
		// system(this);
		system->update();
	}
}

uint32_t ECS::add_entity() {
	int id = this->entities.size();
	this->entities.push_back(id);
	return id;
}

void ECS::add_system(System* sys) {
	this->systems.push_back(sys);
}

// void ECS::add_system(void (*sys)(ECS*)) {
// 	this->systems.push_back(sys);
// }

Query ECS::query_entities() {
	return Query{ .results = this->entities };
}
