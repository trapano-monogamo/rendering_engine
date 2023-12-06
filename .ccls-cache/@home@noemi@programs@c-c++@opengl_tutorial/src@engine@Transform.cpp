#include "engine/Transform.hpp"

eng::Transform::Transform()
    : m_position{1.0f, 1.0f, 1.0f}, m_scale{1.0f, 1.0f, 1.0f}, m_rotation{1.0f, 0.0f, 0.0f, 0.0f}
{}

eng::Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
    : m_position(position), m_scale(scale), m_rotation(rotation)
{}

void eng::Transform::translate(glm::vec3 t) {
	 this->m_position += t;
}
void eng::Transform::rotate(glm::vec3 axis, float angle) {
	 this->m_rotation *= glm::quat(angle, axis);
}
void eng::Transform::scale(glm::vec3 s) {
	 this->m_scale *= s;
}

glm::vec3 eng::Transform::get_position() {
	 return this->m_position;
}
glm::vec3 eng::Transform::get_scale() {
	 return this->m_scale;
}
glm::quat eng::Transform::get_rotation_quat() {
	 return this->m_rotation;
}
glm::vec3 eng::Transform::get_rotation_euler_angles() {
	 return glm::eulerAngles(this->m_rotation);
}
