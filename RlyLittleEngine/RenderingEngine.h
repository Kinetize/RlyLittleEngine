#ifndef RENERINGENGINE_H
#define RENDERINGENGINE_H

#include "Resource.h"
#include "GameObject.h"
#include "Window.h"
#include "Transform.h"
#include "ResourceManager.h"
class Camera : public GameObject {
public:
	Camera(RenderingEngine& rend) :
		Camera(Vector2f(), rend)
	{}

	Camera(const Vector2f& pos, RenderingEngine& rend, float speed = 0.4f) :
		_rendEngine(&rend),
		_pos(Vector2f(pos)),
		_speed(speed)
	{}

	void Update(const float delta, const Input& input) override;

	inline void Move(const Vector2f& dir) { _pos += dir; }
	inline Matrix4f GetTranslation() const { return Matrix4f().MakeTranslation(Vector4f(_pos, 0, 1)); }

	inline Vector2f GetPos() const { return _pos; }
	inline void SetPos(const Vector2f& pos) { _pos = pos; }

	inline void SetSpeed(const float speed) { _speed = speed; }

private:
	RenderingEngine* _rendEngine;

	Vector2f		_pos;
	float			_speed;
};

class RenderingEngine {
public:
	RenderingEngine();
	~RenderingEngine();

	void Init(GameObject* root);
	void ShutDown();
	void Render() const;

	inline void CalcProjection(const float fov, const float zNear, const float zFar, const float aspectRatio) 
		{ _projection.MakeProjection(fov, zNear, zFar, aspectRatio); }
	inline void SetCamTranslation(const Matrix4f& trans) { _camTrans = Matrix4f(trans); }

private:
	bool						_init;
	
	GameObject*					_root;

	Matrix4f					_camTrans;
	Matrix4f					_projection;

	std::vector<resource_key>	_shaders;
	resource_key				_baseMesh;
	resource_key				_baseTexture;
};

#endif