#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#pragma once

#include "GameComponent.h"
#include <vector>

class GameObject {

public:
	GameObject(int temp);

	void UpdateAll();
	void RenderAll() const;

	void AddChildren(GameObject* child);
	void AddComponent(GameComponent* component);

private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	virtual void Update();
	virtual void Render() const;

};




#endif
