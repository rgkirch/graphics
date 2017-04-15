#version 330 core

in vec2 twoTexCo;
out vec4 color;

uniform sampler2D texture;
uniform sampler2D texture1;

void main() {
	//color = texture2D( texture1, twoTexCo );
	color = mix( texture2D( texture, twoTexCo ), texture2D( texture1, twoTexCo ), 0.0f );
	//color = vec4( 0.5f, 0.8f, 0.8f, 1.0f );
}
