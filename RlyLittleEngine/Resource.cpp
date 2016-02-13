#include "ResourceManager.h"
#include "Resource.h"
#include <iostream> //temp

Resource::Resource(GLuint id) :
	_id(id)
{
}


Resource::~Resource() {
}

bool Resource::Init() {
	return true;
}

void Resource::Delete() {

}

void Resource::Bind() const {
}

void Resource::Unbind() const {

}

Shader::Shader(GLuint id) :
	Resource(id),
	_attribCount(0)
{
	if (id != 0) _attribCount = 2;//Tempörär bis shader richtig geladen 
}


Shader::~Shader() {
	if (!_id)
		glDeleteProgram(_id);
}

bool Shader::Init() {
	return true;
}

void Shader::Delete() {
	if (_id)
		glDeleteProgram(_id);
}

void Shader::Bind() const {
	glUseProgram(_id);

	for (int i = 0; i < _attribCount; i++)
		glEnableVertexAttribArray(i);
}

void Shader::Unbind() const {
	glUseProgram(0);

	for (int i = 0; i < _attribCount; i++)
		glDisableVertexAttribArray(i);
}
/*
void Shader::SetUniformF(const std::string& uName, float value) {
	glUniform1f(GetUniformLocation(uName), value);
}

void Shader::SetUniformI(const std::string& uName, int value) {
	glUniform1i(GetUniformLocation(uName), value);
}

GLint Shader::GetUniformLocation(const std::string& uName) {
	if (!_id)
		return -1;

	return glGetUniformLocation(_id, uName.c_str());
	//Error Handling...(GL_INVALID_INDEX
}*/

Mesh::Mesh(GLuint id) :
	Resource(id)
{
}

Mesh::~Mesh() {
}

bool Mesh::Init() {
	return true;
}

void Mesh::Delete() {
	if (_id)
		glDeleteBuffers(1, &_id);
}

void Mesh::Bind() const {
	//TEMP
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	//glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));//Konstanten...
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));//Konstanten...
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Texture::Texture(GLuint id) :
	Resource(id)
{
}

bool Texture::Init() {
	return true;
}

void Texture::Delete() {
	glDeleteTextures(1, &_id);
}

void Texture::Bind() const {
	//glActiveTexture(_id);
	glBindTexture(GL_TEXTURE_2D, _id);
}