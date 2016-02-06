#include "Sprite.h"

Sprite::Sprite(Vector2f pos, Vector2f dimensions, DEPTH_LEVEL dl) :
	GameObject(),
	_mesh(ResourceManager::resource_key_null),
	_texture(ResourceManager::resource_key_null), //deftextur
	_pos(pos),
	_dimensions(dimensions),
	_dl(dl)
{
	Init();
}

Sprite::~Sprite() {
	ResourceManager::UnuseResource(_mesh);
	ResourceManager::UnuseResource(_texture);
}

void Sprite::Init() {	
	std::string temp = "bMesh";
	//_mesh = ResourceManager::UseResource<Mesh>(temp);

	temp = "test.png";
	_texture = ResourceManager::UseResource<Texture>(temp);
}

void Sprite::Update(const float delta) {

}

void Sprite::Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const {//Mesh Klasse...
	if (dl == _dl) {
		ShaderUtil::GetUtil(shader).SetUniformf("a", 0.5f);
		Transform temp = Transform();
		temp.SetTranslation(Vector3f(0, 0, 0));
		ShaderUtil::GetUtil(shader).SetUniformM4f("transform", temp.GetTransformation()); //Transform über rend.engine oder so?
		ResourceManager::CallResource(_texture, FunctionCall::F_BIND);
		ResourceManager::CallResource(mesh, FunctionCall::F_BIND);
	}
}