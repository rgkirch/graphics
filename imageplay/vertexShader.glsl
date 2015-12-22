#version 330 core

in vec3 position;
inout vec2 textureCoordinates;

void main() {
	gl_Position = vec4( position, 1.0 );
}
