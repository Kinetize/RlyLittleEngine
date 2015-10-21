#include "Sprite.h"
#include <iostream>

Sprite::Sprite(Vector2f pos, Vector2f dimensions) :
	GameObject(1),
	_vboID(0),
	_texture(Texture("afdf")),
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
	
	float vertexData[6 * 2]; //Konstanten...

	vertexData[0] = _pos.GetX() + _dimensions.GetX();
	vertexData[1] = _pos.GetY() + _dimensions.GetY();
	vertexData[2] = _pos.GetX();
	vertexData[3] = _pos.GetY() + _dimensions.GetY();
	vertexData[4] = _pos.GetX();
	vertexData[5] = _pos.GetY();

	vertexData[6] = _pos.GetX();
	vertexData[7] = _pos.GetY();
	vertexData[8] = _pos.GetX() + _dimensions.GetX();
	vertexData[9] = _pos.GetY();
	vertexData[10] = _pos.GetX() + _dimensions.GetX();
	vertexData[11] = _pos.GetY() + _dimensions.GetY();

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //Static für den Moment...
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Update() {

}

void Sprite::Render() const {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);//Konstanten...
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}