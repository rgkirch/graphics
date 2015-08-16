#version 330 core

in vec2 twoTexCo;
out vec4 color;

uniform sampler2D texture;
uniform sampler2D texture1;

void main() {
	//color = texture2D( texture1, twoTexCo );
	color = mix( texture2D( texture, twoTexCo ), texture2D( texture1, twoTexCo ), 1.0f );
	//color = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
}
