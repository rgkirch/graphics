#version 330 core

in vec3 color;
layout (location = 0) out vec4 fcolor;

void main() {
	fcolor = vec4(color.r, color.g, color.b, 1.0f);
	//fcolor = vec4(color, 1.0f);
}
