#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

class Texture {
public:
	Texture();

	void Init(unsigned long width, unsigned long height, std::vector<unsigned char>& data);
	void Delete();
	void Bind();

	inline GLuint GetID() const { return _id; }

private:
	GLuint _id; 
};

#endif

