#pragma once

#include <memory>
#include <iostream>
#include "core/mesh.hpp"
#include "core/material.hpp"
#include "core/texture.hpp"
#include "core/shader.hpp"
#include "core/renderable.hpp"

#include "core/scene.hpp"



class GameObject {
public:
	friend class GameObjectBuilder;

private:
	// a GameObject should be managed as an entity by the engine
	Scene* scene = nullptr;
	uint32_t entity = 0;

public:
	GameObject() = default;
	GameObject(Scene*);

	void bind_to_scene(Scene*);

	std::shared_ptr<Renderable> get_renderable();

	std::shared_ptr<Mesh> get_mesh();
	std::shared_ptr<Shader> get_shader();
	std::shared_ptr<Material> get_material();
	std::shared_ptr<Texture> get_texture();

	std::shared_ptr<Transform> get_transform();

	template<typename C> std::shared_ptr<C> get_component();
};

template<typename C>
std::shared_ptr<C> GameObject::get_component() {
	auto c = scene->get_component<C>(entity);
	if (c == nullptr) {
		std::cout << "GameObject doesn't have requested component." << std::endl;
		return nullptr;
	} else {
		return c;
	}
}



class GameObjectBuilder {
private:
	Scene* scene;
	std::shared_ptr<GameObject> go;

	Renderable* tmp_renderable = nullptr;

	void provide_renderable();

public:
	GameObjectBuilder(Scene*);
	~GameObjectBuilder() = default;

	std::shared_ptr<GameObject> build();

	// interface for directly building a renderable:

	GameObjectBuilder& with_mesh(const Mesh&);
	GameObjectBuilder& with_shader(const Shader&);
	GameObjectBuilder& with_material(const Material&);
	GameObjectBuilder& with_texture(const Texture&);

	GameObjectBuilder& with_renderable(const RenderableConfig&);
	GameObjectBuilder& with_transform(const Transform&);

	template<typename C> GameObjectBuilder& with_component(const C&);
};

template<typename C>
GameObjectBuilder& GameObjectBuilder::with_component(const C& c) {
	scene->add_component(go->entity, c);
	return *this;
}
