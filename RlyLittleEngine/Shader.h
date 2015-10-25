#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <string>
#include <fstream>
#include <GL/glew.h>
#include "Util.h"

class Shader {
public:
	Shader();
	~Shader();

	void Compile(const std::string& shaderDir);	
	void Link();

	void AddAttribute(const std::string& attribName);
	void SetUniformF(const std::string& uName, float value);

	void Bind() const;
	void Unbind() const;
private:
	GLuint _programID;
	GLuint _vertexSID;
	GLuint _fragmentSID;

	int _attribCount;

	void CompileShader(const std::string shaderDir, GLuint id);
	GLint GetUniformLocation(const std::string& uName);
};

#endif