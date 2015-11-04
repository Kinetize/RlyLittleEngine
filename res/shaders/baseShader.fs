#version 130

in vec2 texCoord0;

uniform sampler2D gSampler;

out vec4 color;

void main() {
	color = texture2D(gSampler, texCoord0.st);
}