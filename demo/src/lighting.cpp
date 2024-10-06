#include "lighting.hpp"
#include "core/scene.hpp"

// this doesn't work
#define CUSTOM_SHADER_ASSETS_DIRECTORY "/home/chiara/dev/cpp"
#define ENGINE_MODE_3D
#include "engine.hpp"

#include <math.h>
#include <iostream>
#include <memory>



struct SurfaceProperties {
	int N = 100;
	int M = 100;

	float size_x = 20;
	float size_y = 20;
} props;

class SurfaceSystem : public System {
public:

	float v = 1.0f;
	float t = 0.0f;
	unsigned int surface_id;
	Scene* scene;

	SurfaceSystem() = default;
	~SurfaceSystem() = default;

	void update() override {
		auto renderable = scene->get_component<Renderable>(surface_id);
		auto mesh = scene->get_resource<Mesh>(renderable->mesh_key);

		float x{} ,y{};
		for (int i=0; i<props.N; i++) {
			for (int j=0; j<props.M; j++) {
				x = j * props.size_x / props.M;
				y = i * props.size_y / props.N;
				mesh->vertices[i * props.M + j].position = vec3(x, f(x+v*t, y+v*t), y);
				// something's wrong with this:
				mesh->vertices[i * props.M + j].normal = calculate_normal_vector(f, x, y);
			}
		}
		mesh->write_buffers();
	}

	static float f(float x, float y) {
		return sin(x + y);
		// return sqrt(1 - x*x - y*y);
	}
	static float df_dx(float x, float y) { return cos(x+y); }
	static float df_dy(float x, float y) { return cos(x+y); }

	static vec3 calculate_normal_vector(float (*)(float,float), float x, float y) {
		/* 3D surface: z = f(x,y)   =>   g(x,y,z) := f(x,y) - z = 0
		 * normal vector: grad(g(x,y,z)) = (df/dx, df/dy, -1)
		 * */
		return vec3(df_dx(x,y), 1, df_dy(x,y)); // because z is y
	}

	static std::shared_ptr<Mesh> builder() {
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		float x = 0.f, y = 0.f;
		for (int i=0; i<props.N; i++) {
			for (int j=0; j<props.M; j++) {
				x = j * props.size_x / props.M;
				y = i * props.size_y / props.N;
				mesh->vertices.push_back(Vertex{
						vec3(x, f(x,y), y),
						vec3(0, 1, 0),
						vec3(1,1,1),
						vec2(0,0)
					});
				if (i < props.size_y - 1 && j < props.size_x - 1) {
					// first triangle
					mesh->indices.push_back(i     * props.M + j);
					mesh->indices.push_back(i     * props.M + j + 1);
					mesh->indices.push_back((i+1) * props.M + j);
					// second triangle
					mesh->indices.push_back(i     * props.M + j + 1);
					mesh->indices.push_back((i+1) * props.M + j + 1);
					mesh->indices.push_back((i+1) * props.M + j);
				}
			}
		}
		mesh->write_buffers();
		return mesh;
	}
};



std::shared_ptr<Mesh> build_sphere() {
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

	int res_lon = 50;
	int res_lat = 50;

	float lon_inc = 2*PI / res_lon; // increment of longitude angle (res number of points in [0,2pi])
	float lat_inc = 2*PI / res_lat; // increment of longitude angle (res/2 number of points in [0,pi/2])

	mesh->vertices.push_back(Vertex(
		vec3(0, 1, 0), // position
		vec3(0, 1, 0), // normal
		vec3(1, 1, 1), // color
		vec2(0, 0)     // tex coords
	)); // north pole

	for (float phi=PI/2 - lat_inc; phi>-PI/2; phi -= lat_inc) { // latitude
		for (float theta=0; theta<2*PI; theta += lon_inc) { // longitude
			mesh->vertices.push_back(Vertex(
				vec3(sin(theta) * cos(phi), sin(phi), cos(theta) * cos(phi)), // position
				vec3(sin(theta) * cos(phi), sin(phi), cos(theta) * cos(phi)), // normal
				vec3(1, 1, 1), // color
				vec2(0, 0) // tex coords
			));
		}
	}

	mesh->vertices.push_back(Vertex(
		vec3(0, -1, 0), // position
		vec3(0, -1, 0), // normal
		vec3(1, 1, 1),  // color
		vec2(0, 0)      // tex coords
	)); // south pole

	// north pole strip
	for (unsigned int i=0; i<(unsigned int)res_lon; i++) {
		mesh->indices.push_back(0);
		mesh->indices.push_back(i + 2);
		mesh->indices.push_back(i + 1);
	}

	for (unsigned int i=1; i<mesh->vertices.size() - 1; i++) { // poles are excluded
		// first triangle
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
		mesh->indices.push_back(i + res_lon);
		// second triangle
		mesh->indices.push_back(i + 1);
		mesh->indices.push_back(i + res_lon + 1);
		mesh->indices.push_back(i + res_lon);
	}

	// south pole strip
	for (unsigned int i=0; i<(unsigned int)res_lon; i++) {
		mesh->indices.push_back(mesh->vertices.size() - 1);
		mesh->indices.push_back((res_lat-1) * res_lon + i + 1);
		mesh->indices.push_back((res_lat-1) * res_lon + i);
	}

	mesh->write_buffers();
	return mesh;
}



LightingScene::LightingScene(const char* title, int width, int height)
	: GameApp(title, width, height) { }

void LightingScene::on_create() {
	// Shader test = Shader();
	// test.load_from_file("../engine/assets/shaders/light.shader");
	// exit(0);

	// default intialize this
	scene.camera = Camera(vec3(0.0, 1.0, 3.0)).with_perpsective(deg_to_rad(90), 1.0f, 0.1f, 1000.0f);
	// can't this be done in GameApp directly??? yes, it can
	scene.input_handler = InputHandler(this->window);
	scene.background_color = vec3(0.10f, 0.10f, 0.10f);

	scene.register_resource("light_shader",     "../engine/assets/shaders/light.shader");
	scene.register_resource("source_shader",    "../engine/assets/shaders/basic2.shader");
	scene.register_resource("cube_mesh",        "../engine/assets/meshes/cube2.mesh");
	scene.register_resource("bronze_material",  "../engine/assets/materials/bronze.mat");
	scene.register_resource("emerald_material", "../engine/assets/materials/emerald.mat");
	scene.register_resource("sphere_mesh",      build_sphere);

	Transform* sphere_t = new Transform();
	sphere_t->translate(vec3(0,0,-10));
	sphere_t->resize(vec3(7,7,7));
	auto sphere_id = scene.add_entity();
	scene.add_component(sphere_id, sphere_t);
	scene.add_component(sphere_id, new Renderable("sphere_mesh", "bronze_material", "light_shader", ""));

	// Transform* obj1_t = new Transform();
	// obj1_t->translate(vec3(-1.0, 0.0, 0.0));
	// auto obj1_id = scene.add_entity();
	// scene.add_component(obj1_id, new Renderable("cube_mesh", "emerald_material", "light_shader", ""));
	// scene.add_component(obj1_id, obj1_t);

	// Transform* obj2_t = new Transform();
	// obj2_t->translate(vec3(1.0, 0.0, 0.0));
	// auto obj2_id = scene.add_entity();
	// scene.add_component(obj2_id, new Renderable("cube_mesh", "bronze_material", "light_shader", ""));
	// scene.add_component(obj2_id, obj2_t);

	Transform* source_t = new Transform();
	source_t->translate(vec3(1.8f, 2.5f, -1.5f));
	source_t->resize(vec3(.5f, .5f, .5f));
	source_id = scene.add_entity();
	scene.add_component(source_id, new Renderable("cube_mesh", "", "source_shader", ""));
	scene.add_component(source_id, source_t);
	scene.add_component(source_id, new Light(
		source_t->position,
		vec3(1.0f, 1.0f, 1.0f),
		vec3(0.5f, 0.5f, 0.5f),
		vec3(1.0f, 1.0f, 1.0f)
	));


	Transform* surf_t = new Transform();
	surf_t->translate(vec3(0,-3,0));
	auto surf_id = scene.add_entity();
	scene.add_component(surf_id, new Renderable("surface_mesh", "emerald_material", "light_shader", ""));
	scene.add_component(surf_id, surf_t);
	scene.add_component(surf_id, new ObjectRenderingOptions( { .active = false }, true ));

	SurfaceSystem* surf_sys = new SurfaceSystem();
	surf_sys->scene = &scene;
	surf_sys->surface_id = surf_id;
	scene.add_system(surf_sys);

	scene.register_resource("surface_mesh", SurfaceSystem::builder);
}

void LightingScene::on_update(float dt) {
	t += 0.005f;

	scene.get_system<SurfaceSystem>()->t = t;

	light_color = vec3(.5*(1+sin(t)), .5*(1+cos(t)), .5+.5*sin(t)*cos(t));
	for (auto& c : scene.get_resource<Mesh>("cube_mesh")->vertices) c.color = light_color;
	scene.get_component<Light>(source_id)->ambient = vec3(.5*(1+sin(t)), .5*(1+cos(t)), .5 + sin(t)*cos(t));
	scene.get_component<Light>(source_id)->diffuse = vec3(.5*(1+sin(t)), .5*(1+cos(t)), .5 + sin(t)*cos(t));
	scene.get_component<Light>(source_id)->specular = vec3(.5*(1+sin(t)), .5*(1+cos(t)), .5 + sin(t)*cos(t));
	scene.get_resource<Shader>("source_shader")->set_uniform("light_color", light_color, Shader::UniformType::FLOAT_3, 1);
	scene.get_component<Transform>(source_id)->position = vec3(sin(t), cos(t), sin(t)*cos(t)) * 2.0;

	scene.update();

	if (scene.input_handler.is_key_pressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	// if (scene.input_handler.is_key_pressed(GLFW_KEY_X))
	// 	scene.rendering_options.wireframe = true;
	// if (scene.input_handler.is_key_pressed(GLFW_KEY_F))
	// 	scene.rendering_options.wireframe = false;

	if (scene.input_handler.is_key_pressed(GLFW_KEY_W)) {
		vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
		scene.camera.pos += (u * camera_speed * dt);
	}
	if (scene.input_handler.is_key_pressed(GLFW_KEY_S)) {
		vec3 u = vec3::normalize(vec3(scene.camera.dir.x, 0.0, scene.camera.dir.z));
		scene.camera.pos += (-u * camera_speed * dt);
	}
	if (scene.input_handler.is_key_pressed(GLFW_KEY_A))
		scene.camera.pos += (-scene.camera.right * camera_speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_D))
		scene.camera.pos += (scene.camera.right * camera_speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_UP))
		scene.camera.rotate(camera_speed/1.8 * dt, 0.0);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_DOWN))
		scene.camera.rotate(-camera_speed/1.8 * dt, 0.0);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_LEFT))
		scene.camera.rotate(0.0, camera_speed/1.8 * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_RIGHT))
		scene.camera.rotate(0.0, -camera_speed/1.8 * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_SPACE))
		scene.camera.translate(VEC3_Y * camera_speed * dt);
	if (scene.input_handler.is_key_pressed(GLFW_KEY_LEFT_SHIFT))
		scene.camera.translate(-VEC3_Y * camera_speed * dt);

	scene.render();
}
