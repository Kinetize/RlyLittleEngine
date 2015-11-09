#include "ErrorManager.h"

void ErrorManager::Init()
{//Temp
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html";
	std::string msg = "";
	ResourceManager::WriteFile(dir, msg, true);
}

void ErrorManager::SendInformation(InformationType type, std::string& text) {
	WriteToLog(type, text);

	if (type == InformationType::IT_FATALERROR)
		exit(1);
}

void ErrorManager::WriteToLog(InformationType type, std::string& text) {
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html"; //relativ paths
	std::string fText = "";

	switch (type)
	{
	case InformationType::IT_INFO:
		fText = "<font color=#7cfc00><b>[INFO]</b> <font color=#000000>" + text + "<br />";
		break;

	case InformationType::IT_ERROR:
		break;

	case InformationType::IT_FATALERROR:
		break;
	};

	ResourceManager::WriteFile(dir, text);
}
