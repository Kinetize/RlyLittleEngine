#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Area.h"
#include "ResourceManager.h"
#include "Input.h"
#include <vector>

enum DEPTH_LEVEL { //Noch woanders hin moven
	DL_0 = 0, //in front
	DL_1 = 1,
	DL_2 = 2,
	DL_3 = 3 //Background
};

class GameComponent {
public:
	GameComponent();

	virtual void Update(float delta, const Input& input);
	virtual void Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const;

private:

};

class GameObject {

public:
	GameObject();

	void UpdateAll(const float delta, const Input& input);
	void RenderAll(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const;

	void AddChildren(GameObject* child);
	void AddComponent(GameComponent* component);

private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	virtual void Update(const float delta, const Input& input);
	virtual void Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const;

};

#endif