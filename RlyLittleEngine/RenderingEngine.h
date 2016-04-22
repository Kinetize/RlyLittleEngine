#ifndef RENERINGENGINE_H
#define RENDERINGENGINE_H

#include "Resource.h"
#include "GameObject.h"
#include "Window.h"
#include "Transform.h"
#include "ResourceManager.h"

class Light;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	void Init(GameObject* root);
	void ShutDown();
	void Render() const;

	inline void AddLight(Light* light) { _lights.push_back(light); }
	inline void RemoveLight(Light* light) { _lights.remove(light); }

private:
	bool											_init;
	
	GameObject*										_root;

	std::unordered_map<resource_key, ShaderType>	_shaders;
	std::list<Light*>								_lights;
	resource_key									_baseMesh;
	resource_key									_baseTexture;
};

#endif