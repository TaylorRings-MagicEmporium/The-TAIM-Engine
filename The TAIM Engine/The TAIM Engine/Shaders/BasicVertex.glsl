#version 330

in vec3 LVertexPos2D; 
void main() { 
gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, LVertexPos2D.z, 1 ); 
}