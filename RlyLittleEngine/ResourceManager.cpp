#include "ResourceManager.h"
#include <iostream> //temp

std::vector<TexResource> ResourceManager::_textures = std::vector<TexResource>();

bool ResourceManager::ReadFile(std::string& fileDir, std::vector<unsigned char>& content) {//Nur momentan public...
	std::ifstream file(fileDir, std::ios::binary);

	if (!file)
		return false;

	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(0, std::ios::beg);
	size -= file.tellg();

	content.resize(size);
	file.read((char *)&(content[0]), size);

	file.close();

	return true;
}

std::string ResourceManager::ReadFile(std::string fileDir) { //Unschöne, temporäre Methode, Nur momentan public...
	std::ifstream file(fileDir);

	if (!file)
		return "";

	std::string content = "";
	std::string line;

	while (std::getline(file, line)) {
		content += line + "\n";
	}

	file.close();

	return content;
}

bool ResourceManager::WriteFile(std::string& fileDir, std::string& text, bool clearFile) {
	std::fstream file;
	
	if(clearFile)
		file = std::fstream(fileDir, std::ios::out | std::ios::trunc);
	else
		file = std::fstream(fileDir, std::ios::out | std::ios::app);

	if (!file)
		return false;

	file << std::endl << text;

	file.close();

	return true;
}

Texture* ResourceManager::UseTexture(std::string& fileDir) {
	int index = TexInMap(fileDir);
	if (index > -1) {
		_textures[index].users++;
		return &_textures[index].tex;
	}

	//if(fileDir.size() > 3 && fileDir.substr(fileDir.size() - 4, fileDir.size() - 1).compare(".png")) //eig bei "." splitten
		return LoadPNGTexture(fileDir);
	//else
	//	return LoadPNGTexture(fileDir); //Eigentlich Fehlermeldung, anderer Dateityp o.ä.
}

void ResourceManager::UnuseTexture(Texture* texture) {
	int index = TexInMap(texture);

	if (index > -1) {		
		if (--_textures[index].users < 1) {
			//Element löschen, Texure ausm Speicher kicken, Vector auffüllen etc
		}
	}
}

Texture* ResourceManager::LoadPNGTexture(std::string& fileDir) { //nicht zufrieden mit Aufteilung
	std::vector<unsigned char> inData, outData;
	unsigned long width, height;
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/textures/" + fileDir; //relativ paths...
	if (!ReadFile(dir, inData))
		std::cout << "texfile error" << std::endl;

	if (decodePNG(outData, width, height, &inData[0], inData.size()) != 0)
		std::cout << "pico error " << std::endl;

	_textures.push_back(TexResource());
	_textures[_textures.size() - 1].fileDir = fileDir;
	_textures[_textures.size() - 1].tex.Init(width, height, outData);
	_textures[_textures.size() - 1].users = 1;

	return &_textures[_textures.size() - 1].tex;//texturen löschen...
}

int ResourceManager::TexInMap(std::string& text) { //verallgemeinern mit Templates/Lambda

	int index = -1;

	for (auto& element : _textures) {
		index++;

		if (element.fileDir.compare(text) == 0)
			return index;
	}

	return -1;
}

int ResourceManager::TexInMap(Texture* tex) { //verallgemeinern mit Templates/Lambda

	int index = -1;

	for (auto& element : _textures) {
		index++;

		if (element.tex.GetID() == tex->GetID())
			return index;
	}

	return -1;
}