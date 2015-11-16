#ifndef MESH_H
#define MESH_H
#pragma once

#include <GL/glew.h>
#include "Vertex.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	void Draw() const;

	void Delete();

	inline GLuint GetID() { return _vboID; }
	inline GLuint* GetIDPTR() { return &_vboID; }
private:
	GLuint	 _vboID;
};

#endif
