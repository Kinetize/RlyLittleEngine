#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#pragma once

#include "Mesh.h"
#include "Area.h"
#include "Shader.h"
#include "GameComponent.h"
#include <vector>

class GameComponent; //sollte weg...

class GameObject {

public:
	GameObject(int temp);

	void UpdateAll(float delta);
	void RenderAll(const Shader* shader, const Mesh* mesh, const Area area) const;

	void AddChildren(GameObject* child);
	void AddComponent(GameComponent* component);

private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	virtual void Update(float delta);
	virtual void Render(const Shader* shader, const Mesh* mesh, const Area area) const;

};




#endif
