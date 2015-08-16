#version 330 core

// declare inputs with the 'in' keyword
// set the location to be used later
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCo;
out vec2 twoTexCo;

void main() {
	gl_Position = vec4( position, 1.0 );
	twoTexCo = texCo;
}
