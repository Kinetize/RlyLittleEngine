struct Attenuation {
	float linear;
	float exponent;
};

struct Light {
	vec3 color;
	float intensity;
};

struct PointLight {
	Light light;
	vec3 position;
	Attenuation attenuation;
};

struct DirectionalLight {
	PointLight pLight;
	vec2 direction;
	float angle;
};
