#include "Sprite.h"

Sprite::Sprite(Vector2f pos, Vector2f dimensions) :
	GameObject(1),
	_texture(Texture("afdf")),
	_pos(pos),
	_dimensions(dimensions)
{
}

void Sprite::Update() {

}

void Sprite::Render() const {

}