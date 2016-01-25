#include "Mesh.h"

Mesh::Mesh() :
	Resource()
{
}


Mesh::~Mesh() {
}

bool Mesh::Init() {
	return true;
}

void Mesh::Delete() {
	if (_vboID)
		glDeleteBuffers(1, &_vboID);
}

void Mesh::Draw() const {
	//TEMP
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));//Konstanten...
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));//Konstanten...
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}