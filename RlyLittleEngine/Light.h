#ifndef LIGHT_H
#define LIGHT_H

#include "MMath.h"
#include "GameObject.h"
#include "RenderingEngine.h"

class Attenuation {
public:
	Attenuation(float linear = 0.0f, float exponent = 1.0f) :
		_linear(linear),
		_exponent(exponent)
	{}

private:
	float _linear;
	float _exponent;
};

class Light : public GameComponent {
public:
	Light(RenderingEngine* engine = nullptr, Vector3f color = Vector3f(255, 255, 255), float intensity = 1.0f) :
		GameComponent(COMPONENT_TYPE::CT_LIGHT),
		_color(Vector3f(color)),
		_intensity(intensity)
	{
		AddToRendering(engine);
	}

	~Light() {
		if (_engine != nullptr)
			_engine->RemoveLight(this);
	}

	inline Vector3f GetColor() const { return _color; }
	inline float GetIntensity() const { return _intensity; }

	inline void SetColor(Vector3f color) { _color = Vector3f(color); }
	inline void SetColor(float intensity) { _intensity = intensity; }

	inline void AddToRendering(RenderingEngine* engine) { if(engine != nullptr) _engine = engine; _engine->AddLight(this); }

private:
	RenderingEngine*	_engine;

	Vector3f			_color;
	float				_intensity;
};

class PointLight : public Light {
public:
	PointLight(Vector3f pos = Vector3f(0, 0, 0), Attenuation attenuation = Attenuation(0, 0), RenderingEngine* engine = nullptr, Vector3f color = Vector3f(255, 255, 255), float intensity = 1.0f) :
		Light(engine, color, intensity),
		_pos(Vector3f(pos)),
		_attenuation(attenuation)
	{}

private:
	Vector3f	_pos;

	Attenuation _attenuation;
};

class DirectionalLight : public PointLight {
public:
	DirectionalLight(Vector2f direction = Vector2f(1, 1), float angle = 1.0f, Vector3f pos = Vector3f(0, 0, 0), Attenuation attenuation = Attenuation(0, 0), RenderingEngine* engine = nullptr,
		Vector3f color = Vector3f(255, 255, 255), float intensity = 1.0f) :
		PointLight(engine, angle, pos, attenuation, color, intensity),
		_direction(direction),
		_angle(angle)
	{}

private:
	Vector2f	_direction;

	float		_angle;
};

#endif