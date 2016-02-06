#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "MMath.h"

//Erst 3D f�r Ebenene, sp�ter Zugang �ber Methoden f�r 2D
//IN SHADER ATM NOCH Z = 1!!!!!!
class Transform {
public:
	Matrix4f GetTransformation() const;

	inline Vector3f GetTranslation() const { return _translation; }
	inline Vector3f SetTranslation(float x, float y, float z) { _translation.Set(x, y, z); }

private:
	Vector3f _translation;
};

#endif