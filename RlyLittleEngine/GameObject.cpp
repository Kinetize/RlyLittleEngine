#include "GameObject.h"

GameObject::GameObject() :
	children(std::vector<GameObject*>(0)),
	components(std::vector<GameComponent*>(0))
{

}

void GameObject::UpdateAll(const float delta, const Input& input) {
	Update(delta, input);

	for (auto & element : children) {
		element->UpdateAll(delta, input);
	}

	for (auto & element : components) {
		element->Update(delta, input);
	}
}

void GameObject::RenderAll(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const {
	Render(shader, mesh, dl, area);

	for (auto & element : children) {
		element->RenderAll(shader, mesh, dl, area);
	}

	for (auto & element : components) {
		element->Render(shader, mesh, dl, area);
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

void GameObject::Update(const float delta, const Input& input) {

}

void GameObject::Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const {

}

GameComponent::GameComponent()
{
}

void GameComponent::Update(float delta, const Input& input) {

}

void GameComponent::Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const {

}