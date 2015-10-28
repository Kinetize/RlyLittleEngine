#include "ResourceManager.h"
#include <iostream> //temp

/*void ResourceManager::Init() {
	_textures = std::map<std::string, Texture>();
	_textures.insert(std::pair<std::string, Texture>("defTex", Texture())); //ToDo: Def Textur
}*/

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
	
	_textures.insert(std::pair<std::string, Texture>(fileDir, Texture()));

	/*GLuint tex_2d = SOIL_load_OGL_texture("/res/textures/" + fileDir, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	if (!tex_2d)
	{
		//Error...
	}*/


	Texture* texd = &Texture();
	return texd;
}
