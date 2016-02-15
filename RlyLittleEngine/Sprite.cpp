#include "Sprite.h"

Sprite::Sprite(Vector2f& pos, Vector2f& dimensions, const std::string& texDir, DEPTH_LEVEL dl) :
	GameObject(),
	_texture(ResourceManager::UseResource<Texture>(texDir)), //deftextur
	_transform(Transform()),
	_dl(dl)
{
	_transform.SetTranslation(Vector3f(pos, dl * 0.000000000000000001f));
	_transform.SetScale(Vector3f(dimensions, 1));
}

Sprite::~Sprite() {
	ResourceManager::UnuseResource(_texture);
}

void Sprite::Update(const float delta, const Input& input) {
	_transform.GetTransformation();
}

void Sprite::Render(const resource_key shader, const resource_key mesh, const DEPTH_LEVEL dl, const Area area) const {//Mesh Klasse...
	if (dl == _dl) {
		ShaderUtil::GetUtil(shader).SetTransformation(_transform.GetLastTransformation()); //Transform über rend.engine oder so?
		ResourceManager::CallResource(_texture, FunctionCall::F_BIND);
		ResourceManager::CallResource(mesh, FunctionCall::F_BIND);
	}
}