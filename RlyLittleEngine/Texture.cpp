#include "Texture.h"

Texture::Texture(int id) :
	_id(id)
{ 
}

void Texture::Init() {
	glGenTextures(1, &_id);
	glTexParameterf(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::Delete() {
	glDeleteTextures(1, &_id);
}


void Texture::Bind() {
	glActiveTexture(_id);
	glBindTexture(GL_TEXTURE_2D, _id);
}


