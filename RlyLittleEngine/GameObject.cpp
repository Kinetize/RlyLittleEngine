#include "GameObject.h"

GameObject::GameObject(int temp) :
	children(std::vector<GameObject*>(0)),
	components(std::vector<GameComponent*>(0))
{

}

void GameObject::UpdateAll() {	
	Update();

	for (auto & element : children) {
		element->UpdateAll();
	}

	for (auto & element : components) {
		element->Update();
	}
}

void GameObject::RenderAll() const {
	Render();

	for (auto & element : children) {
		element->RenderAll();
	}

	for (auto & element : components) {
		element->Render();
	}
}

void GameObject::AddChildren(GameObject* child) {
	for (auto & element : children) {
		if (element == child)
			return;
	}
	children.push_back(child);
}

void GameObject::AddComponent(GameComponent* component) {
	for (auto & element : components) {
		if (element == component)
			return;
	}
	components.push_back(component);
}

void GameObject::Update() {

}

void GameObject::Render() const {

}