#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec3 vert_color;
out vec2 tex_coords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main() {
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	vert_color = aColor;
	tex_coords = aTexCoords;
}
