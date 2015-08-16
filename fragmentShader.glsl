#version 330 core

in vec2 twoTexCo;
out vec4 color;

uniform sampler2D texture;

void main() {
	color = texture2D( texture, twoTexCo );
	//color = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
}
