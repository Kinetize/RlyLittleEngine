#include "ErrorManager.h"
#include "ResourceManager.h"
#include "Game.h"

bool ErrorManager::_init = false;
Game* ErrorManager::_game = nullptr;

void ErrorManager::Init(Game* game) {//Temp
	if (_init) {
		std::string inf = "ErrorManager tried to be initialized twize";
		SendInformation(InformationType::IT_ERROR, inf);
	}
	
	_game = game;
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/Log.html";
	std::string msg = "";
	ResourceManager::WriteFile(dir, msg, true);

	_init = true;
	std::string inf = "ErrorManager initialized";
	ErrorManager::SendInformation(InformationType::IT_INFO, inf);
}

void ErrorManager::ShutDown() {
	if (_init) {
		std::string inf = "ErrorManager shut down";
		SendInformation(InformationType::IT_INFO, inf);
		_init = false;
	}
	else {
		std::string inf = "ErrorManager tried to be shut down while not being initialized";
		SendInformation(InformationType::IT_ERROR, inf);
	}
}

void ErrorManager::SendInformation(InformationType type, std::string& text) {
	if (!_init)
		return;

	WriteToLog(type, text);

	if (type == InformationType::IT_FATALERROR) {
		_game->Stop(InformationType::IT_FATALERROR);
	}
}

void ErrorManager::WriteToLog(InformationType type, std::string& text) {
	if (!_init) {
		std::cout << "Tried to write to log while not being initilized. Msg: " + text << std::endl;
		return;
	}

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
		fText = "<font color=#8b0000><b>[FATALERROR]</b> <font color=#000000>" + text + " <br /><font color=#8b0000><i>Program will exit</i><br />";
		break;
	};

	ResourceManager::WriteFile(dir, fText);
}
