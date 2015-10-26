#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include <string>
#include <fstream>
#include <vector>

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	static bool readFile(std::string fileDir, std::vector<char>& content); //Nur momentan public...
	static std::string readFile(std::string fileDir); //Unschöne, temporäre Methode, Nur momentan public...

private:
	
	
};

#endif

