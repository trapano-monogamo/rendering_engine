#include "ecs/ecs.hpp"

ECS::~ECS() { 
	for (auto entry : this->components)
		for (Component* c : entry.second)
			delete c;
}

void ECS::update() {
	for (auto sys : this->systems) {
		sys(*this);
	}
}

void ECS::add_entity(uint32_t entity) {
	this->entities.push_back(Entity{entity});
}

void ECS::add_system(void (*sys)(ECS&)) {
	this->systems.push_back(sys);
}
