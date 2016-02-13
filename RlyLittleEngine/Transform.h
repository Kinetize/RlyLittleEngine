#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "MMath.h"

class RenderingEngine;

//Erst 3D für Ebenene, später Zugang über Methoden für 2D
//IN SHADER ATM NOCH Z = 1!!!!!!
class Transform { //Noch rotation um ursprung mit -> trns um ursprung, drehen, zurück
public:
	Transform() :
		_transform(Matrix4f()),
		_translation(Vector3f()),
		_rotation(Vector3f()),
		_scale(Vector3f(1, 1, 1)),
		_changed(true)
	{}

	Matrix4f& GetTransformation();

	inline Vector3f GetTranslation() const { return _translation; }
	inline void SetTranslation(const Vector3f& trans) { _changed = true; _translation = Vector3f(trans); }

	inline Vector3f GetRotation() const { return _rotation; }
	inline void SetRotation(const Vector3f& rot) { _changed = true; _rotation = Vector3f(rot); }

	inline Vector3f GetScale() const { return _scale; }
	inline void SetScale(const Vector3f& scale) { _changed = true; _scale = Vector3f(scale); }
	
private:
	Matrix4f _transform;

	Vector3f _translation;
	Vector3f _rotation;
	Vector3f _scale;

	bool	 _changed;
};

#endif