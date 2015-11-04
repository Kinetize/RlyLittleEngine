#version 130

in vec2 pos;
in vec2 texCoord;

out vec2 texCoord0;

uniform float time;

void main() { 
	gl_Position	= vec4(pos * sin(time), 0, 1);

	texCoord0 = texCoord;	
}