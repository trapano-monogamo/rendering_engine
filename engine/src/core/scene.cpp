#include "core/scene.hpp"
#include "core/mesh.hpp"
#include "core/renderable.hpp"
#include "core/shader.hpp"
#include "math/mat.hpp"
#include "math/utils.hpp"

Scene::Scene()
	: camera(Camera(vec3(0.0, 0.0, 0.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 100.0f))
{}

void Scene::render() {
	mat4 view = mat4::lookat(this->camera.pos, this->camera.up, this->camera.right, this->camera.dir);

	auto query = this->query_entities()
			.with_component<Renderable>(this)
			.results;

	// for (auto& entity : query) {
	// 	std::cout << "entity: " << entity << "\t" << get_component<Renderable>(entity) << std::endl;
	// }

	for (auto& entity : query) {
		Renderable* obj = this->get_component<Renderable>(entity);

		mat4 transform = mat4::transform(obj->scale, obj->euler_rotations, obj->position);

		auto mesh = get_resource<Mesh>(obj->mesh_key);
		auto shader = get_resource<Shader>(obj->shader_key);

		shader->set_uniform_matrix_4fv("transform", transform.m);
		shader->set_uniform_matrix_4fv("view", view.m);
		shader->set_uniform_matrix_4fv("projection", this->camera.projection.m);

		// obj->texture.use();
		// ~ Mesh and Shader are mandatory for rendering ~
		mesh->use();
		shader->use();
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}
