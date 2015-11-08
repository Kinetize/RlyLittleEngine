#include "ErrorManager.h"

void ErrorManager::Init()
{//Temp
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html";
	std::string msg = "";
	ResourceManager::WriteFile(dir, msg, true);
}

void ErrorManager::SendInformation(InformationType type, std::string& text) {
	switch (type)
	{
	case InformationType::IT_INFO:
		WriteToLog(type, text);
		break;

	case InformationType::IT_ERROR:
		WriteToLog(type, text);
		break;

	case InformationType::IT_FATALERROR:
		WriteToLog(type, text);
		exit(1);
		break;
	};
}

void ErrorManager::WriteToLog(InformationType type, std::string& text) {
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html"; //relativ paths
	ResourceManager::WriteFile(dir, text); //HTML Formatierung je nach Typ etc
}
