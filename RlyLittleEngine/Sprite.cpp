#include "Sprite.h"

Sprite::Sprite(Vector2f pos, Vector2f dimensions) :
	GameObject(),
	_mesh(nullptr),
	_texture(nullptr), //deftextur
	_pos(pos),
	_dimensions(dimensions)
{
	Init();
}

Sprite::~Sprite() {
	ResourceManager::UnuseResource<Mesh>(_mesh);
	ResourceManager::UnuseResource<Texture>(_texture);
}

void Sprite::Init() {	
	std::string temp = "";
	_mesh = ResourceManager::UseResource<Mesh>(temp);

	temp = "test.png";
	_texture = ResourceManager::UseResource<Texture>(temp);
}

void Sprite::Update(const float delta) {

}

void Sprite::Render(const Shader* shader, const Mesh* mesh, const Area area) const {//Mesh Klasse...
	_mesh->Draw();
}