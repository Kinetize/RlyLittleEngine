#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include "Vector2f.h"
#include "Vector4b.h"

struct Vertex {/*Vertex Struct nur temporär da unschön in momentaner form */
	inline Vertex() : pos(Vector2f(0, 0)), texCoord(Vector2f(0, 0)) {}

	Vector2f	pos;
	Vector2f	texCoord;
};

#endif