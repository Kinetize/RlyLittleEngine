#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
public:
	Texture(int id);

private:
	GLuint _id; 
};

#endif

