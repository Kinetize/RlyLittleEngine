#ifndef RENERINGENGINE_H
#define RENDERINGENGINE_H

#include "Resource.h"
#include "GameObject.h"
#include "Window.h"
#include "ResourceManager.h"

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	void Init(GameObject* root);
	void ShutDown();
	void Render() const;

private:
	bool						_init;
	
	GameObject*					_root;

	std::vector<resource_key>	_shaders;
	resource_key				_baseMesh;
	resource_key				_baseTexture;
};

#endif