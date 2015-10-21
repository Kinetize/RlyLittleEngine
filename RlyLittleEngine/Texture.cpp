#include "Texture.h"



Texture::Texture(std::string fileDir) :
	_vboID(0)
{
	loadTexture(fileDir);
}

bool Texture::loadTexture(std::string fileDir) {
	return true;
}

