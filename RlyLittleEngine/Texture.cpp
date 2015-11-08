#include "Texture.h"
#include <iostream>//temp

Texture::Texture() : 
	_id(0)
{ 
}

void Texture::Init(unsigned long width, unsigned long height, std::vector<unsigned char>& data) {
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, NULL);


	if (!_id)
	{
		std::cout << "errorTex; ID:" + _id << std::endl;
		//Error...
	}
}

void Texture::Delete() {
	glDeleteTextures(1, &_id);
}


void Texture::Bind() {
	//glActiveTexture(_id);
	glBindTexture(GL_TEXTURE_2D, _id);
}


