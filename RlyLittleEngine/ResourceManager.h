#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include <fstream>
#include <vector>
#include "SOIL/SOIL.h"
#include "Util.h"

struct TexResource { //anstatt map?
	TexResource() : fileDir(""), tex(Texture(-1)), users(-1) {};

	std::string fileDir;
	Texture tex;
	int users;
};

class ResourceManager {
public:
	static bool readFile(std::string& fileDir, std::vector<char>& content); //Nur momentan public...
	static std::string readFile(std::string fileDir); //Unschöne, temporäre Methode, Nur momentan public...

	static Texture* UseTexture(std::string& fileDir);
	static void UnuseTexture(Texture* tex);

private:
	static std::vector<TexResource> _textures; //Int zählt die Anzahl der Nutzer --> <= 0? Löschen
	
	static Texture* LoadPNGTexture(std::string& fileDir);//.../res/textures mit rein nehmen; def Texture
	static int TexInMap(std::string& text); //verallgemeinern?
	static int TexInMap(Texture* tex); //verallgemeinern?
};

#endif

