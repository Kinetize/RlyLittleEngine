#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include "GameComponent.h"
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <string>

class Texture : GameComponent {
public:
	Texture(std::string fileDir);

	virtual void Update() override;
	virtual void Render() const override;

private:
	

	bool loadTexture(std::string fileDir);
};

#endif

