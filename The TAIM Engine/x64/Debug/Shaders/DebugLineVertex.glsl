#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 outColor;

uniform mat4 View;
uniform mat4 Proj;

vec4 DefaultCol = vec4(1.0,1.0,1.0,1.0);

void main(){
	gl_Position = Proj * View * vec4(aPos,1.0);
	outColor = DefaultCol;
}