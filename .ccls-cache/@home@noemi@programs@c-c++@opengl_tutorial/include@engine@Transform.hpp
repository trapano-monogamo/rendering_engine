#pragma once
#include "common_opengl.hpp"

namespace eng
{


class Transform
{
private:
	 glm::vec3 m_position;
	 glm::vec3 m_scale;
	 glm::quat m_rotation;

public:
	 Transform();
	 Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation);
	 ~Transform() = default;

	 void translate(glm::vec3 t);
	 void rotate(glm::vec3 axis, float angle);
	 void scale(glm::vec3 s);

	 glm::vec3 get_position();
	 glm::vec3 get_scale();
	 glm::quat get_rotation_quat();
	 glm::vec3 get_rotation_euler_angles();
};


}
