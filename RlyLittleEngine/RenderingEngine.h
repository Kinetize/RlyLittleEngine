#ifndef RENERINGENGINE_H
#define RENDERINGENGINE_H

#include "Resource.h"
#include "GameObject.h"
#include "Window.h"
#include "Transform.h"
#include "ResourceManager.h"

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	void Init(GameObject* root);
	void ShutDown();
	void Render() const;

	void CalcProjection(const float fov, const float zNear, const float zFar, const float aspectRatio);

private:
	bool						_init;
	
	GameObject*					_root;

	Matrix4f					_projection;

	std::vector<resource_key>	_shaders;
	resource_key				_baseMesh;
	resource_key				_baseTexture;
};

#endif