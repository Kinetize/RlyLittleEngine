#include "Transform.h"

Matrix4f& Transform::GetTransformation() {
	if (!_changed)
		return _transform;

	Matrix4f trans, rot, scale;
	trans.MakeTranslation(Vector4f(_translation, 1));
	rot.MakeRotation(Vector4f(_rotation, 1));
	scale.MakeScale(Vector4f(_scale, 1));

	_transform = trans * rot * scale;
	return _transform;
}