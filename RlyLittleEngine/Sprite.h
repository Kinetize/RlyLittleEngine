#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include "Vertex.h"
#include "Vector2f.h"
#include "GameObject.h"
#include "Texture.h"

class Sprite : public GameObject {
public:
	Sprite(Vector2f pos, Vector2f dimensions);
	~Sprite();

private:
	GLuint	 _vboID;
	Texture _texture;
	
	Vector2f _pos;
	Vector2f _dimensions;

	void Init();
	void Update() override;
	void Render() const override;
};

#endif
