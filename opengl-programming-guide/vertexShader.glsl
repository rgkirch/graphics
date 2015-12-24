#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 scolor;
out vec3 tcolor;

void main() {
	gl_Position = vec4( position, 1.0 );
    tcolor = scolor;
}
