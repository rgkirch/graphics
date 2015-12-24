#version 330 core

in vec3 vcolor;
out vec4 fcolor;

void main() {
	fcolor = vec4(vcolor, 1.0f);
}
