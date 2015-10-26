#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

bool ResourceManager::readFile(std::string fileDir, std::vector<char>& content) {//Nur momentan public...
	std::ifstream file(fileDir, std::ios::binary);

	if (!file)
		return false;
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
