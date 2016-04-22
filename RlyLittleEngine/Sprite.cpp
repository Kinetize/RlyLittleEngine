#include "Sprite.h"

Sprite::Sprite(Vector2f pos, Vector2f dimensions, DEPTH_LEVEL dl, float rotation, const std::string& texDir) :
	GameObject(),
	_mesh(ResourceManager::resource_key_null),
	_texture(ResourceManager::resource_key_null), //deftextur
	_pos(pos),
	_dimensions(dimensions),
	_dl(dl),
	_rotation(rotation)
{
	Init(texDir);
}

Sprite::~Sprite() {
	ResourceManager::UnuseResource(_mesh);
	ResourceManager::UnuseResource(_texture);
}

void Sprite::Init(const std::string& texDir) {	//Quite useless
	_texture = ResourceManager::UseResource<Texture>(texDir);
}

void Sprite::Update(const float delta) {

}

void Sprite::Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const {//Mesh Klasse...
	if (dl == _dl) {
		Transform temp = Transform();
		temp.SetTranslation(_pos);
		temp.SetRotation(Vector3f(0, 0, _rotation));
		temp.SetScale(_dimensions);
		ShaderUtil::GetUtil(shader).SetUniformM4f("transform", temp.GetTransformation()); //Transform über rend.engine oder so?
		ResourceManager::CallResource(_texture, FunctionCall::F_BIND);
		ResourceManager::CallResource(mesh, FunctionCall::F_BIND);
	}
}