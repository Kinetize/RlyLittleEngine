#version 130

in vec2 texCoord0;

uniform sampler2D gSampler;

uniform vec3 lightPos;
uniform vec3 lightStrenght;
uniform vec3 lightAttributes;

out vec4 color;

void main() {
	//gl_FragColor = texture2D(gSampler, texCoord0.xy);
	//color = vec4(texCoord0.xy, 0, 1);
	color = texture2D(gSampler, texCoord0.xy);
}