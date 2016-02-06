#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "MMath.h"

//Erst 3D für Ebenene, später Zugang über Methoden für 2D
//IN SHADER ATM NOCH Z = 1!!!!!!
class Transform {
public:
	Transform() :
		_translation(Vector3f())
	{}

	Matrix4f GetTransformation() const;

	inline Vector3f GetTranslation() const { return _translation; }
	inline void SetTranslation(const Vector3f& trans) { _translation = Vector3f(trans); }
	inline void SetTranslation(const float x, const float y, const float z) { _translation.Set(x, y, z); }

private:
	Vector3f _translation;
};

#endif