#include "Sprite.h"

Sprite::Sprite(Vector2f pos, Vector2f dimensions) :
	GameObject(1),
	_vboID(0),
	_texture(nullptr), //deftextur
	_pos(pos),
	_dimensions(dimensions)
{
	Init();
}

Sprite::~Sprite() {
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void Sprite::Init() {
	if (_vboID != 0)
		return;
	
	glGenBuffers(1, &_vboID);
	
	/*Vertex Struct nur tempor�r da unsch�n in momentaner form */Vertex vertexData[6]; //Konstanten...
	vertexData[0].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[0].pos.SetY(_pos.GetY() + _dimensions.GetY());
	vertexData[1].pos.SetX(_pos.GetX());
	vertexData[1].pos.SetY(_pos.GetY() + _dimensions.GetY());
	vertexData[2].pos.SetX(_pos.GetX());
	vertexData[2].pos.SetY(_pos.GetY());

	vertexData[3].pos.SetX(_pos.GetX());
	vertexData[3].pos.SetY(_pos.GetY());
	vertexData[4].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[4].pos.SetY(_pos.GetY());
	vertexData[5].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[5].pos.SetY(_pos.GetY() + _dimensions.GetY());

	vertexData[0].texCoord.SetX(1.0f);
	vertexData[0].texCoord.SetY(1.0f);
	vertexData[1].texCoord.SetX(0.0f);
	vertexData[1].texCoord.SetY(1.0f);
	vertexData[2].texCoord.SetX(0.0f);
	vertexData[2].texCoord.SetY(0.0f);
		
	vertexData[3].texCoord.SetX(0.0f);
	vertexData[3].texCoord.SetY(0.0f);
	vertexData[4].texCoord.SetX(1.0f);
	vertexData[4].texCoord.SetY(0.0f);
	vertexData[5].texCoord.SetX(1.0f);
	vertexData[5].texCoord.SetY(1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //Static f�r den Moment...
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Update(const float delta) {

}

void Sprite::Render(const Shader* shader, const Mesh* mesh, const Area area) const {//Mesh Klasse...
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));//Konstanten...
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));//Konstanten...
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}