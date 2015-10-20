#include "GameObject.h"

GameObject::GameObject() :
	children(std::vector<GameObject*>(1))
{

}

void GameObject::UpdateAll() {	
	Update();

	for (auto & element : children) {
		element->UpdateAll();
	}
}

void GameObject::RenderAll() const {
	Render();

	for (auto & element : children) {
		element->RenderAll();
	}
}

void GameObject::AddChildren(GameObject* child) {
	for (auto & element : children) {
		if (element == child)
			return;
	}
	children.push_back(child);
}