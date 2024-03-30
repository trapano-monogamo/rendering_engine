#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aCol;
layout (location = 3) in vec2 aTexCoords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

uniform vec3 light_color;

out vec3 vert_color;

void main() {
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	vert_color = light_color;
}

#shader fragment
#version 330 core

in vec3 vert_color;
out vec4 frag_color;

void main() {
	frag_color = vec4(vert_color, 0.0);
}
