#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H
#pragma once

#include "GameObject.h"

class GameComponent {
public:
	GameComponent();

	virtual void Update(float delta);
	virtual void Render(const Shader* shader, const Mesh* mesh, const Area area) const;

private:

};

#endif