#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include "ResourceManager.h"
#include "mmath.h"
#include "GameObject.h"
#include "Transform.h"

class Sprite : public GameObject {
public:
	Sprite(Vector2f& pos, Vector2f& dimensions, const std::string& texDir = "test.png", DEPTH_LEVEL dl = DEPTH_LEVEL::DL_2);
	~Sprite();

private:
	resource_key	_texture;
	
	Transform		_transform;
	DEPTH_LEVEL		_dl;

	void Update(const float delta, const Input& input) override;
	void Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const override;
};

#endif
