#include "engine/Renderable.hpp"
#include "my_utils.hpp"
#include <iostream>

eng::Renderable::Renderable()
	 : Transform()
{
	 float vertices[] = {
		  -0.5, -0.5, -0.5,   1.0, 0.0, 0.0,
		   0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
		   0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
		  -0.5,  0.5, -0.5,   1.0, 0.0, 0.0,
		  -0.5, -0.5,  0.5,   0.0, 1.0, 0.0,
		   0.5, -0.5,  0.5,   0.0, 0.0, 1.0,
		   0.5,  0.5,  0.5,   1.0, 0.0, 0.0,
		  -0.5,  0.5,  0.5,   0.0, 1.0, 0.0,
	 };

	 unsigned int indices[] = {
		  0, 1, 3, 3, 1, 2,
		  1, 5, 2, 2, 5, 6,
		  5, 4, 6, 6, 4, 7,
		  4, 0, 7, 7, 0, 3,
		  3, 2, 7, 7, 2, 6,
		  4, 5, 0, 0, 5, 1
	 };

	 this->va = VertexArray(sizeof(vertices), vertices, sizeof(indices), indices);
	 this->shader = Shader("../res/vertex.shader", "../res/fragment.shader");

	 std::cout << typeid(this->shader.program).name() << " " << (bool)glIsProgram(this->shader.program) << std::endl;
	 exit(0);
}

void eng::Renderable::draw()
{
	 glm::mat4 transform = glm::mat4(1.0f);
	 transform = glm::translate(transform, this->get_position());
	 transform = glm::rotate(transform, this->get_rotation_euler_angles()[0], glm::vec3(1.0f, 0.0f, 0.0f));
	 transform = glm::rotate(transform, this->get_rotation_euler_angles()[0], glm::vec3(0.0f, 1.0f, 0.0f));
	 transform = glm::rotate(transform, this->get_rotation_euler_angles()[0], glm::vec3(0.0f, 0.0f, 1.0f));
	 transform = glm::scale(transform, this->get_scale());

	 //this->shader.set_uniform_matrix_4fv("transform", transform);

	 this->shader.use();
	 this->va.use();
	 glDrawElements(GL_TRIANGLES, this->va.vert_count, GL_UNSIGNED_INT, 0);
	 unbind_all();
}
