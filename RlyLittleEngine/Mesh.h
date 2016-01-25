#ifndef MESH_H
#define MESH_H
#pragma once

#include <GL/glew.h>
#include "Resource.h"
#include "Vertex.h"

class Mesh : Resource {
public:
	Mesh();
	~Mesh();

	bool Init() override;
	void Delete() override;

	void Draw() const;

	inline GLuint GetID() { return _vboID; }
	inline GLuint* GetIDPTR() { return &_vboID; }
private:
	GLuint	 _vboID;
};

#endif
