#include "core/game_object.hpp"
#include <iostream>


/* ..:: GameObject ::.. */

GameObject::GameObject(Scene* s)
	: scene(s)
	, entity(s->add_entity())
{ }

void GameObject::bind_to_scene(Scene* s) { scene = s; }

Renderable* GameObject::get_renderable() {
	return scene->get_component<Renderable>(entity);
}

Mesh* GameObject::get_mesh() {
	auto r = get_renderable();
	if (r != nullptr) {
		auto res = scene->get_resource<Mesh>(r->mesh_key).get();
		if (res == nullptr) std::cout << "GameObject doesn't use a Mesh." << std::endl;
		return res;
	} else {
		std::cout << "GameObject has no Renderable component." << std::endl;
		return nullptr;
	}
}

Shader* GameObject::get_shader() {
	auto r = get_renderable();
	if (r != nullptr) {
		auto res = scene->get_resource<Shader>(r->shader_key).get();
		if (res == nullptr) std::cout << "GameObject doesn't use a Shader." << std::endl;
		return res;
	} else {
		std::cout << "GameObject has no Renderable component." << std::endl;
		return nullptr;
	}
}

Material* GameObject::get_material() {
	auto r = get_renderable();
	if (r != nullptr) {
		auto res = scene->get_resource<Material>(r->material_key).get();
		if (res == nullptr) std::cout << "GameObject doesn't use a Material." << std::endl;
		return res;
	} else {
		std::cout << "GameObject has no Renderable component." << std::endl;
		return nullptr;
	}
}

Texture* GameObject::get_texture() {
	auto r = get_renderable();
	if (r != nullptr) {
		auto res = scene->get_resource<Texture>(r->texture_key).get();
		if (res == nullptr) std::cout << "GameObject doesn't use a Texture." << std::endl;
		return res;
	} else {
		std::cout << "GameObject has no Renderable component." << std::endl;
		return nullptr;
	}
}




/* ..:: GameObjectBuilder ::.. */

GameObjectBuilder::GameObjectBuilder(Scene* scene)
	: scene(scene)
	, go(new GameObject())
{
	go->entity = scene->add_entity();
	go->scene = scene;
}

std::shared_ptr<GameObject> GameObjectBuilder::build() {
	if (tmp_renderable != nullptr)
		scene->add_component(go->entity, tmp_renderable);

	return go;
}

void GameObjectBuilder::provide_renderable() {
	if (tmp_renderable == nullptr) tmp_renderable = new Renderable{"", "", "", ""};
}



// GameObjectBuilder& GameObjectBuilder::with_mesh(const Mesh& m) {
// 	provide_renderable();
// 	scene->register_resource<Mesh>();
// 	return *this;
// }
// 
// GameObjectBuilder& GameObjectBuilder::with_shader(const Shader& s) {
// 	provide_renderable();
// 	// ...
// 	return *this;
// }
// 
// GameObjectBuilder& GameObjectBuilder::with_material(const Material& m) {
// 	provide_renderable();
// 	// ...
// 	return *this;
// }
// 
// GameObjectBuilder& GameObjectBuilder::with_texture(const Texture& t) {
// 	provide_renderable();
// 	// ...
// 	return *this;
// }

GameObjectBuilder& GameObjectBuilder::with_renderable(const RenderableConfig& config) {
	if (!config.mesh.key.empty()) scene->register_resource<Mesh>(config.mesh);
	if (!config.material.key.empty()) scene->register_resource<Material>(config.material);
	if (!config.shader.key.empty()) scene->register_resource<Shader>(config.shader);
	if (!config.texture.key.empty()) scene->register_resource<Texture>(config.texture);

	scene->add_component(go->entity, new Renderable(config.mesh.key, config.material.key, config.shader.key, config.texture.key));
	return *this;
}

GameObjectBuilder& GameObjectBuilder::with_transform(const Transform& t) {
	scene->add_component(go->entity, new Transform(t));
	return *this;
}
