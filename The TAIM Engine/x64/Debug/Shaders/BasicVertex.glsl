#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 View;
uniform mat4 Proj;

void main() { 
gl_Position = Proj * View * model * vec4( aPos, 1 ); 
}