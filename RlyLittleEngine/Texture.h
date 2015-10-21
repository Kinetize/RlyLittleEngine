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

private:
	GLuint	 _vboID;

	bool loadTexture(std::string fileDir);
};

#endif

