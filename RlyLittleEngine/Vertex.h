#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include "Vector2f.h"
#include "Vector4b.h"

struct Vertex {/*Vertex Struct nur tempor�r da unsch�n in momentaner form */
	inline Vertex() : pos(Vector2f(0, 0)), color(Vector4b(0, 0, 0, 0)) {}

	Vector2f	pos;
	Vector4b	color;
};

#endif