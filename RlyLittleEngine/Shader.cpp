#include "Shader.h"
#include <iostream> //temp

Shader::Shader() :
	_programID(0),
	_vertexSID(0),
	_fragmentSID(0),
	_attribCount(0)
{ 
}


Shader::~Shader() {
	if(!_programID)
		glDeleteProgram(_programID);
}

void Shader::Compile(const std::string& shaderDir) {//.../res/shaders mit rein nehmen 
	if (_programID != 0 | _vertexSID != 0 || _fragmentSID != 0)
		return;

	_programID = glCreateProgram();
	_vertexSID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentSID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!_programID | !_vertexSID || !_fragmentSID)
		return;

	CompileShader(shaderDir + ".vs", _vertexSID);
	CompileShader(shaderDir + ".fs", _fragmentSID);
}

void Shader::Link() {
	glAttachShader(_programID, _vertexSID);
	glAttachShader(_programID, _fragmentSID);

	glLinkProgram(_programID);

	GLint linked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, &linked);

	if (!linked) {
		glDeleteProgram(_programID);
		glDeleteShader(_vertexSID);
		glDeleteShader(_fragmentSID);
		std::cout << "couldnt link shader" << std::endl;
		return;
	}

	glDetachShader(_programID, _vertexSID);
	glDetachShader(_programID, _fragmentSID);
	glDeleteShader(_vertexSID);
	glDeleteShader(_fragmentSID);
}

void Shader::AddAttribute(const std::string& attribName) {
	if (!_programID)
		return;

	glBindAttribLocation(_programID, _attribCount++, attribName.c_str());
}

void Shader::SetUniformF(const std::string& uName, float value) {
	glUniform1f(GetUniformLocation(uName), value);
}

void Shader::Bind() const {
	glUseProgram(_programID);

	for (int i = 0; i < _attribCount; i++)
		glEnableVertexAttribArray(i);
}

void Shader::Unbind() const {
	glUseProgram(0);

	for (int i = 0; i < _attribCount; i++)
		glDisableVertexAttribArray(i);
}

void Shader::CompileShader(const std::string& shaderDir, GLuint id) {
	std::string content = ResourceManager::readFile(shaderDir);
	const char* contentPtr = content.c_str(); //Dirty...
	glShaderSource(id, 1, &contentPtr, nullptr);

	glCompileShader(id);

	GLint sucess = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {//Error Log etc
		GLint logSize = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);

		std::vector<GLchar> errorLog(logSize);
		glGetShaderInfoLog(id, logSize, &logSize, &errorLog[0]);
		std::string log(errorLog.begin(), errorLog.end());
		std::cout << "couldnt compile shader" << std::endl;
		std::cout << log << std::endl;

		glDeleteShader(id);
		return;
	}
}

GLint Shader::GetUniformLocation(const std::string& uName) {
	if (!_programID)
		return -1;

	return glGetUniformLocation(_programID, uName.c_str());
	//Error Handling...(GL_INVALID_INDEX
}