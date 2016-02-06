#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <DevIL/il.h>
#include "SOIL/SOIL.h"
#include "Resource.h"
#include "Util.h"
#include "picoPNG.h"
#include "ErrorManager.h"

typedef unsigned long resource_key;

//SHADER ATTRIBCOUNT

class ResourceLoader 
{
public:
	template<class T> static GLuint LoadResource(const std::string& fileDir);

private://Not to happy...
	static void CompileShader(const std::string& fileDir, GLuint& id);
	static void AddAttributeToShader(GLuint& id, int& attribCount, const std::string& attribName);
	static void LinkShader(const GLuint& id, const GLuint& vId, const GLuint& fId);

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