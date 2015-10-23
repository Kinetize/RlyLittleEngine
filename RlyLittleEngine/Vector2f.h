#ifndef VECTOR2F_H
#define VECTOR2F_H
#pragma once

#include <string>

class Vector2f
{
public:
	Vector2f(float x = 0.0f, float y = 0.0f);

	inline float GetX() const { return _x; }
	inline float GetY() const { return _y; }

	inline void SetX(float x) { _x = x; }
	inline void SetY(float y) { _y = y; }

	inline std::string ToString() const { return "X: " + std::to_string(_x) + "Y: " + std::to_string(_y); }

private:
	float	_x;
	float	_y;
};

#endif
