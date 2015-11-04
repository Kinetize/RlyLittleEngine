#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
public:
	Texture(int id);

	void Init();
	void Delete();
	void Bind();

	inline GLuint GetID() const { return _id; }

private:
	GLuint _id; 
};

#endif

