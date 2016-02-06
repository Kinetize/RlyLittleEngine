#include "ErrorManager.h"
#include "ResourceManager.h"
#include "Game.h"

bool ErrorManager::init = false;
std::string ErrorManager::logPath;
Game* ErrorManager::game = nullptr;

void ErrorManager::Init(Game* game) {//Temp
	if (init) {
		std::string inf = "ErrorManager tried to be initialized twize";
		SendInformation(InformationType::IT_ERROR, inf);
	}
	
	game = game;
	logPath = "../Log.html";
	std::string msg = "";
	ResourceManager::WriteFile(logPath, msg, true);

	init = true;
	std::string inf = "ErrorManager initialized";
	ErrorManager::SendInformation(InformationType::IT_INFO, inf);
}

void ErrorManager::ShutDown() {
	if (init) {
		std::string inf = "ErrorManager shut down";
		SendInformation(InformationType::IT_INFO, inf);
		init = false;
	}
	else {
		std::string inf = "ErrorManager tried to be shut down while not being initialized";
		SendInformation(InformationType::IT_ERROR, inf);
	}
}

void ErrorManager::SendInformation(InformationType type, std::string& text) {
	if (!init)
		return;

	WriteToLog(type, text);

	if (type == InformationType::IT_FATALERROR) {
		game->Stop(InformationType::IT_FATALERROR);
	}
}

void ErrorManager::WriteToLog(InformationType type, std::string& text) {
	if (!init) {
		std::cout << "Tried to write to log while not being initilized. Msg: " + text << std::endl;
		return;
	}

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

	ResourceManager::WriteFile(logPath, fText);
}
