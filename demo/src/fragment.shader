#version 330 core

in vec2 tex_coords;
in vec3 vert_color;
in vec3 vert_pos;
out vec4 frag_color;

uniform sampler2D tex;

void main() {
	frag_color = vec4(vert_color * texture(tex, vec2(vert_pos.xz)).xyz, 1.0);
}
