#include "GameObject.h"

GameObject::GameObject(int temp) :
	children(std::vector<GameObject*>(0)),
	components(std::vector<GameComponent*>(0))
{

}

void GameObject::UpdateAll(float delta) {
	Update(delta);

	for (auto & element : children) {
		element->UpdateAll(delta);
	}

	for (auto & element : components) {
		element->Update(delta);
	}
}

void GameObject::RenderAll(const Shader* shader, const Mesh* mesh, const Area area) const {
	Render(shader, mesh, area);

	for (auto & element : children) {
		element->RenderAll(shader, mesh, area);
	}

	for (auto & element : components) {
		element->Render(shader, mesh, area);
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

void GameObject::Update(float delta) {

}

void GameObject::Render(const Shader* shader, const Mesh* mesh, const Area area) const {

}