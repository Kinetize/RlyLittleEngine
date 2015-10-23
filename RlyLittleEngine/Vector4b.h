#ifndef VECTOR4B_H
#define VECTOR4B_H
#pragma once

#include <GL/glew.h>

class Vector4b
{
public:
	Vector4b(GLubyte x, GLubyte y, GLubyte z, GLubyte w);

	inline float GetX() const { return _x; }
	inline float GetY() const { return _y; }
	inline float GetZX() const { return _z; }
	inline float GetZ() const { return _w; }

	inline void SetX(GLubyte x) { _x = x; }
	inline void SetY(GLubyte y) { _y = y; }
	inline void SetZ(GLubyte z) { _z = z; }
	inline void SetW(GLubyte w) { _w = w; }

private:
	GLubyte	_x;
	GLubyte	_y;
	GLubyte _z;
	GLubyte _w;

};

#endif
