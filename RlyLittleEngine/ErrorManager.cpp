#include "ErrorManager.h"

bool ErrorManager::init = false;

void ErrorManager::Init()
{//Temp
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html";
	std::string msg = "";
	ResourceManager::WriteFile(dir, msg, true);

	init = true;
}

void ErrorManager::SendInformation(InformationType type, std::string& text) {
	if (!init)
		Init();
	
	WriteToLog(type, text);

	if (type == InformationType::IT_FATALERROR)
		exit(1);
}

void ErrorManager::WriteToLog(InformationType type, std::string& text) {
	if (!init)
		Init();

	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html"; //relativ paths
	std::string fText = "";

	switch (type)
	{
	case InformationType::IT_INFO:
		fText = "<font color=#7cfc00><b>[INFO]</b> <font color=#000000>" + text + "<br />";
		break;

	case InformationType::IT_ERROR:
		fText = "<font color=#000080><b>[ERROR]</b> " + text + "<br />";
		break;

	case InformationType::IT_FATALERROR:
		fText = "<font color=#8b0000><b>[FATAERROR]</b> <font color=#000000>" + text + " <br /><font color=#8b0000><i>Program will exit</i><br />";
		break;
	};

	ResourceManager::WriteFile(dir, fText);
}
