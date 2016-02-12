#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "SOIL/SOIL.h"
#include "Resource.h"
#include "Util.h"
#include "picoPNG.h"
#include "ErrorManager.h"

typedef unsigned long resource_key;

//SHADER ATTRIBCOUNT

class ShaderUtil {
public:
	ShaderUtil() :
		_id(0),
		_attribCount(0),
		_uniforms(std::unordered_map<std::string, GLuint>())
	{}

	GLuint Init(const std::string& fileDir, resource_key key); //MÄÄÄÄH - Attributes etc
	void AddUniform(const std::string& name);
	inline void SetUniformi(const std::string& name, const int val) { glUniform1i(_uniforms[name],val); } //passt der Zugriff per name...?
	void SetUniformf(const std::string& name, const float val) { glUniform1f(_uniforms[name], val); }
	void SetUniformV3f(const std::string& name, const Vector3f& val) { glUniform3f(_uniforms[name], val.GetX(), val.GetY(), val.GetZ()); }
	//Some Error floating aroung the uniforms/translation
	void SetUniformM4f(const std::string& name, Matrix4f& val) { val.SetUniform(_uniforms[name]);
		GLfloat a[4][4];
		//a[0][0] = 1;
		//a[1][1] = 1;
		//a[2][2] = 1;
		//a[3][3] = 1;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (i != j)
					a[i][j] = 0;
				else
					a[i][j] = 1;

		//glUniformMatrix4fv(_uniforms[name], 1, true, &a[0][0]);
		//Matrix4f().MakeIdentity().SetUniform(_uniforms[name]);
	}

	static inline ShaderUtil& GetUtil(const resource_key key) { return utils[key]; }
	static inline void DeleteUtil(const resource_key key) { utils.erase(key); }

private:
	static std::unordered_map<resource_key, ShaderUtil> utils;

	GLuint _id;
	unsigned int _attribCount;
	std::unordered_map<std::string, GLuint> _uniforms;

	void Compile(const std::string& fileDir, GLuint& id);
	void Link(const GLuint& vId, const GLuint& fId);
	void AddAttribute(const std::string& attribName);
};

class ResourceLoader { //Net so das "ware"
public:
	template<class T> static GLuint LoadResource(const std::string& fileDir);

private://Not to happy...
	static void LoadPNGTexture(const std::string& fileDir, unsigned long& width, 
		unsigned long& height, std::vector<unsigned char>& data);//.../res/textures mit rein nehmen; def Texture
};

struct ResourceTupel { 
	ResourceTupel() : resource(nullptr), fileDir(""), users(-1) {};

	std::unique_ptr<Resource> resource;
	std::string fileDir;
	int users;
};

class ResourceManager { //+Guard über offene Files; File Read in Loader?
public:
	static void Init();
	static void ShutDown();

	static bool ReadFile(const std::string& fileDir, std::vector<unsigned char>& content); //Nur momentan public...
	static std::string ReadFile(const std::string& fileDir); //Unschöne, temporäre Methode, Nur momentan public...

	static bool WriteFile(const std::string& fileDir, const std::string& text, bool clearFile = false);

	template<class T> static resource_key UseResource(const std::string& fileDir);
	static void UnuseResource(const resource_key key);

	static void CallResource(const resource_key key, const FunctionCall func);//Mäh

	static const resource_key GetActKey() { return nextKey; }
	static const resource_key resource_key_null;

private:
	static bool												live;

	static std::unordered_map<resource_key, ResourceTupel>	resources;
	static std::vector<std::string>							openFiles; //ToDo... aber: sinnvoll? Schließlich keine Threads, aber wenn kein close...

	static resource_key										nextKey;

	static resource_key ResInMap(const std::string& text);
	static bool ResInMap(const resource_key key);
};

#endif