#pragma once
#include "common_opengl.hpp"
#include "engine/VertexArray.hpp"
#include "engine/Shader.hpp"
#include "engine/Transform.hpp"

namespace eng
{


class Renderable : public Transform
{
public:
	 VertexArray va;
	 Shader shader;

	 Renderable();
	 ~Renderable() = default;

	 void load_model(const char* obj_filepath); // TODO
	 void laod_shader(const char* vertex_filepath, const char* fragmen_filepath);

	 void draw();
};


}
