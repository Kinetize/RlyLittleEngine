#version 130

in vec2 pos;
in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 transform;

void main() { 
	gl_Position	= transform * vec4(pos, 1, 1);

	texCoord0 = texCoord;	
}