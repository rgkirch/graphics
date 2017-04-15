#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vcolor;

uniform mat4 projection;
uniform mat4 view;

out vec3 fcolor;

void main() {
    fcolor = vcolor;
    gl_Position = projection * (view * vec4(position, 1.0f));
    //gl_Position = vec4(position, 1.0f);
}
