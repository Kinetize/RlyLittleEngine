#include "ResourceManager.h"
#include <iostream> //temp

std::vector<TexResource> ResourceManager::_textures = std::vector<TexResource>();
//std::map<std::string, int> ResourceManager::_resourceGuard = std::map<std::string, int>();

bool ResourceManager::readFile(std::string& fileDir, std::vector<char>& content) {//Nur momentan public...
	std::ifstream file(fileDir, std::ios::binary);

	if (!file)
		return false;

	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(0, std::ios::beg);
	size -= file.tellg();

	content.resize(size);
	file.read(&(content[0]), size);

	file.close();

	return true;
}

std::string ResourceManager::readFile(std::string fileDir) { //Unschöne, temporäre Methode, Nur momentan public...
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

Texture* ResourceManager::UseTexture(std::string& fileDir) {
	int index = TexInMap(fileDir);
	if (index > -1) {
		_textures[index].users++;
		return &_textures[index].tex;
	}

	if(fileDir.size() > 3 && fileDir.substr(fileDir.size() - 4, fileDir.size() - 1).compare(".png"))
		return LoadPNGTexture(fileDir);
	else
		return LoadPNGTexture(fileDir); //Eigentlich Fehlermeldung, anderer Dateityp o.ä.
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
	std::string dir = "/res/textures/" + fileDir;
	GLuint id = SOIL_load_OGL_texture(dir.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (!id)
	{
		//Error...
	}
 
	TexResource textureElement; //Naja...
	textureElement.fileDir = fileDir;
	textureElement.tex = Texture(id);
	textureElement.tex.Init();
	textureElement.users = 1;
	_textures.push_back(textureElement);

	return &textureElement.tex;//texturen löschen...
}

int ResourceManager::TexInMap(std::string& text) { //verallgemeinern?

	int index = -1;

	for (auto& element : _textures) {
		index++;

		if (element.fileDir.compare(text) == 0)
			return index;
	}

	return -1;
}

int ResourceManager::TexInMap(Texture* tex) { //verallgemeinern?

	int index = -1;

	for (auto& element : _textures) {
		index++;

		if (element.tex.GetID() == tex->GetID())
			return index;
	}

	return -1;
}