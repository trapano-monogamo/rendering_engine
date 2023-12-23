#include "core/scene.hpp"
#include "core/renderable.hpp"
#include "core/transform.hpp"
#include "math/mat.hpp"
#include "math/utils.hpp"

Scene::Scene()
	: camera(Camera(vec3(0.0, 0.0, 0.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 100.0f))
{}

void Scene::render() {
	mat4 view = mat4::lookat(this->camera.pos, this->camera.up, this->camera.right, this->camera.dir);

	auto query = this->query_entities()
			.with_component<Renderable>(this)
			.with_component<Transform>(this)
			.results;

	for (auto& entity : query) {
		Renderable* obj = this->get_component<Renderable>(entity);
		Transform* t = this->get_component<Transform>(entity);

		mat4 transform = mat4::transform(t->scale, vec3(), 0.0, t->position);

		obj->program.set_uniform_matrix_4fv("transform", transform.m);
		obj->program.set_uniform_matrix_4fv("view", view.m);
		obj->program.set_uniform_matrix_4fv("projection", this->camera.projection.m);

		obj->texture.use();
		obj->va.use();
		obj->program.use();
		glDrawElements(GL_TRIANGLES, obj->va.elements_count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
