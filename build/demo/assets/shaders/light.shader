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

void main() {
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	vert_color = aCol;
}

#shader fragment
#version 330 core

in vec3 vert_color;
out vec4 frag_color;

uniform float shininess;
uniform vec3 light;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

void main() {
	// frag_color = vec4(vert_color, 1.0);
	frag_color = vec4(light_color * vert_color, 0.0);
}
