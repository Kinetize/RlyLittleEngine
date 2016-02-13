#ifndef RESOURCE_H
#define RESOURCE_H

#include <GL/glew.h>
#include "mmath.h"

struct Vertex {/*Vertex Struct nur tempor�r da unsch�n in momentaner form */
	inline Vertex() : pos(Vector3f(0, 0, 0)), texCoord(Vector2f(0, 0)) {}

	Vector3f	pos;
	Vector2f	texCoord;
};

enum FunctionCall { //M�h
	F_INIT,
	F_DELETE,
	F_BIND,
	F_UNBIND
};

//Init raus?
class Resource
{
public:
	Resource(GLuint id);
	~Resource();

	virtual bool Init();
	virtual void Delete();

	virtual void Bind() const;
	virtual void Unbind() const;

	virtual inline GLuint GetID() const { return _id; }

protected:
	GLuint _id;
};

class Shader : public Resource {
public:
	Shader(GLuint id);
	~Shader();

	bool Init() override;
	void Delete() override;

	void Bind() const override;

	//void SetUniformF(const std::string& uName, float value);
	//void SetUniformI(const std::string& uName, int value);

	void Unbind() const;

private:
	int _attribCount;

	//GLint GetUniformLocation(const std::string& uName);
};

class Mesh : public Resource {
public:
	Mesh(GLuint id);
	~Mesh();

	bool Init() override;
	void Delete() override;

	void Bind() const override;
	//inline GLuint* GetIDPTR() { return &_vboID; }
};

class Texture : public Resource {
public:
	Texture(GLuint id);

	virtual bool Init() override;
	virtual void Delete() override;

	void Bind() const override;
};

#endif

