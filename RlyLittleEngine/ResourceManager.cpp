#include "ResourceManager.h"
#include <iostream> //temp

std::map<std::string, Texture> ResourceManager::_textures = std::map<std::string, Texture>();

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

Texture* ResourceManager::LoadPNGTexture(std::string& fileDir) {
	std::pair<std::string, Texture> element = Util::PosStringInMap(_textures, fileDir);
	if (element.first.compare("NotFound")) {
		std::cout << "Bereits geladen" << std::endl;
		return &element.second;
	}
	
	std::string dir = "/res/textures/" + fileDir + ".png";
	GLuint id = SOIL_load_OGL_texture(dir.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (!id)
	{
		//Error...
	}

	std::pair<std::string, Texture> textureElement = std::pair<std::string, Texture>(fileDir, Texture(id));
	_textures.insert(textureElement);

	return &textureElement.second;//texturen löschen...
}
