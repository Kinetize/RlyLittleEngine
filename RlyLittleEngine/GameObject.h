#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Area.h"
#include "ResourceManager.h"
#include <vector>

enum DEPTH_LEVEL {
	DL_0, //in front
	DL_1,
	DL_2,
	DL_3 //Background
};

enum COMPONENT_TYPE {//Mäh
	CT_CASUAL,
	CT_LIGHT
};

class GameComponent {
public:
	GameComponent(COMPONENT_TYPE type = COMPONENT_TYPE::CT_CASUAL);

	virtual void Update(float delta);
	virtual void Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const;

private:
	COMPONENT_TYPE _type; //Mäh
};

class GameObject {

public:
	GameObject();

	void UpdateAll(const float delta);
	void RenderAll(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const;

	void AddChildren(GameObject* child);
	void AddComponent(GameComponent* component);

private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;

	virtual void Update(const float delta);
	virtual void Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const;

};

#endif