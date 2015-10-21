#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include <GL/glew.h>
#include "Vector2f.h"
#include "GameObject.h"
#include "Texture.h"

class Sprite : GameObject {
public:
	Sprite(Vector2f pos, Vector2f dimensions);

private:
	Texture _texture;

	Vector2f _pos;
	Vector2f _dimensions;

	void Update() override;
	void Render() const override;
};

#endif
