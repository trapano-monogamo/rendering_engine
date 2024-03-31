#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aCol;
layout (location = 3) in vec2 aTexCoords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

out vec3 vert_color;
out vec3 vert_normal;
out vec3 frag_pos;

void main() {
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	vert_color = aCol;
	// vert_normal = aNorm;
	vert_normal = mat3(transpose(inverse(transform))) * aNorm;  
	frag_pos = vec3(transform * vec4(aPos, 1.0));
}

/* ------------------------------------------------------------------ */

#shader fragment
#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 pos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 vert_color;
in vec3 vert_normal;
in vec3 frag_pos;

uniform vec3 view_pos;
uniform vec3 light_pos;
uniform vec3 light_color;

uniform Material material;
uniform Light light;

out vec4 frag_color;

void main() {
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(vert_normal);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// specular
	vec3 view_dir = normalize(view_pos - frag_pos);
	vec3 reflect_dir = reflect(-light_dir, norm); 
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular) * vert_color;
	frag_color = vec4(result, 1.0);
}
