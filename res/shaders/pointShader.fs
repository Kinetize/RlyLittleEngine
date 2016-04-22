#version 130

#include "Light.h"

in vec2 texCoord0;

uniform sampler2D gSampler;

uniform vec3 lightPos;
uniform vec3 lightStrenght;
uniform vec3 lightAttributes;

out vec4 color;

void main() {
	color = texture2D(gSampler, texCoord0.xy);
}