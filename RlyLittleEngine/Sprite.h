#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include "ResourceManager.h"
#include "mmath.h"
#include "GameObject.h"

class Sprite : public GameObject {
public:
	Sprite(Vector2f pos, Vector2f dimensions, DEPTH_LEVEL dl);
	~Sprite();

private:
	resource_key	_mesh;
	resource_key	_texture;
	
	Vector2f	_pos;
	Vector2f	_dimensions;
	DEPTH_LEVEL	_dl;

	void Init();
	void Update(const float delta) override;
	void Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const override;
};

#endif
