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

struct TexResource { //anstatt map?
	TexResource() : fileDir(""), tex(Texture()), users(-1) {};

	std::string fileDir;
	Texture tex;
	int users;
};

class ResourceManager { //+Guard über offene Files...
public: 
	static bool ReadFile(std::string& fileDir, std::vector<unsigned char>& content); //Nur momentan public...
	static std::string ReadFile(std::string fileDir); //Unschöne, temporäre Methode, Nur momentan public...

	static bool WriteFile(std::string& fileDir, std::string& text, bool clearFile = false);

	static Texture* UseTexture(std::string& fileDir);
	static void UnuseTexture(Texture* tex);

private:
	static std::vector<TexResource> _textures; //Int zählt die Anzahl der Nutzer --> <= 0? Löschen
	
	static Texture* LoadPNGTexture(std::string& fileDir);//.../res/textures mit rein nehmen; def Texture
	static int TexInMap(std::string& text); //verallgemeinern mit Templates/Lambda?
	static int TexInMap(Texture* tex); //verallgemeinern mit Templates/Lambda?
};

#endif

