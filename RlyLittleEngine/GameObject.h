#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#pragma once

#include <vector>

class GameObject {

public:
	GameObject();

	void UpdateAll();
	void RenderAll() const;

	void AddChildren(GameObject* child);

private:
	std::vector<GameObject*> children;

	virtual void Update();
	virtual void Render() const;
};




#endif
