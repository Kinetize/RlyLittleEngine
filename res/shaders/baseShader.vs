#version 330

in vec2 pos;
in vec4 color;

out vec4 fragColor;

uniform float time;

void main() { 
	gl_Position	= vec4(pos, 0, 1);

	fragColor = color;	
}