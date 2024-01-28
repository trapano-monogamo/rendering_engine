#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

out vec3 vert_color;

void main() {
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	vert_color = aCol;
}
