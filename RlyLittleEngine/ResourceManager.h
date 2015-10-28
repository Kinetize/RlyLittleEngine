#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include <fstream>
#include <vector>
#include "SOIL/SOIL.h"
#include "Util.h"

class ResourceManager {
public:
	static bool readFile(std::string& fileDir, std::vector<char>& content); //Nur momentan public...
	static std::string readFile(std::string fileDir); //Unschöne, temporäre Methode, Nur momentan public...
	static Texture LoadPNGTexture(std::string& fileDir);//.../res/textures mit rein nehmen 

private:
	static std::map<std::string, Texture> _textures;
	
};

#endif

