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
	
	/*Vertex Struct nur temporär da unschön in momentaner form */Vertex vertexData[6]; //Konstanten...
	
	vertexData[0].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[0].pos.SetX(_pos.GetY() + _dimensions.GetY());
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

	for (int i = 0; i < 6; i++) { //Konstanten...
		vertexData[i].color.SetX(255);
		vertexData[i].color.SetY(255);
		vertexData[i].color.SetZ(0);
		vertexData[i].color.SetW(255);
	}
		

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //Static für den Moment...
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Update(float delta) {

}

void Sprite::Render(const Shader* shader, const Mesh* mesh, const Area area) const {//Mesh Klasse...
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));//Konstanten...
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) offsetof(Vertex, color));//Konstanten...
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}