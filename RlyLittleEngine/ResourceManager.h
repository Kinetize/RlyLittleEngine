#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include <fstream>
#include <vector>
#include <DevIL/il.h>
#include "SOIL/SOIL.h"
#include "Util.h"
#include "picoPNG.h"
#include "ErrorManager.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Shader.h"

//resource-Oberklasse für Shader, Mesh, Texture? Dann alles in einen Vector?
template<class T>
struct Resource { 
	Resource() : resource(T()), fileDir(""), users(-1) {};

	T resource;
	std::string fileDir;
	int users;
};

class ResourceManager { //+Guard über offene Files...
public:
	static bool ReadFile(std::string& fileDir, std::vector<unsigned char>& content); //Nur momentan public...
	static std::string ReadFile(std::string fileDir); //Unschöne, temporäre Methode, Nur momentan public...

	static bool WriteFile(std::string& fileDir, std::string& text, bool clearFile = false);

	template<class T> static T* UseResource(std::string& fileDir);
	template<class T> static void UnuseResource(T* tex);

private:
	static std::vector<Resource<Shader>>	_shaders;
	static std::vector<Resource<Mesh>>		_meshes;
	static std::vector<Resource<Texture>>	_textures;
	
	template<class T> static void InitResource();
	template<class T> static int ResInVector(std::string& text);
	template<class T> static int ResInVector(T* tex); 
	template<class T> static std::vector<Resource<T>>* GetSuitableVector();
	static void LoadPNGTexture(std::string& fileDir);//.../res/textures mit rein nehmen; def Texture
};

#endif