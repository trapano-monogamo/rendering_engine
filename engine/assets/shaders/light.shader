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
	vert_normal = aNorm;
	frag_pos = vec3(transform * vec4(aPos, 1.0));
}

#shader fragment
#version 330 core

in vec3 vert_color;
in vec3 vert_normal;
in vec3 frag_pos;

out vec4 frag_color;

uniform vec3 light_pos;
uniform vec3 light_color;

uniform float ambient;

void main() {
	vec3 norm = normalize(vert_normal);
	vec3 dir = normalize(light_pos - frag_pos);

	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * light_color;

	vec3 result = (ambient + diffuse) * vert_color;

	frag_color = vec4(result, 0.0);
}
