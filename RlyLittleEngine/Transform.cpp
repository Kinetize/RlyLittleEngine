#include "Transform.h"

Matrix4f Transform::GetTransformation() const {
	Matrix4f trans;
	trans.MakeTranslation(Vector4f(_translation, 1));

	return trans;
}