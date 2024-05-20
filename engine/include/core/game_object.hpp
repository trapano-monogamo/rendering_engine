#pragma once

#include "engine.hpp"

class GameObject {
private:
	std::shared_ptr<Renderable> r;
	std::shared_ptr<Scene> s;

public:
	GameObject();
	~GameObject() = default;

	/* the user calls Scene::add_game_object(...) which
	 * creates an object and binds the scene to the newly created obj
	 * */
	void bind_scene(/*Scene* s*/);

	void build_from_resources(/* const std::string& ...key, ...*/);
	void build_from_data(/* const Mesh&, ... */);

	std::shared_ptr<Mesh>		get_mesh();
	std::shared_ptr<Material>	get_material();
	std::shared_ptr<Texture>	get_texture();
	std::shared_ptr<Shader>		get_shader();
};
