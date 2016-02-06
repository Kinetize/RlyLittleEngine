#include "ErrorManager.h"
#include "ResourceManager.h"
#include "Game.h"

bool ErrorManager::init = false;
std::string ErrorManager::logPath;
Game* ErrorManager::game = nullptr;

void ErrorManager::Init(Game* game) {//Temp
	if (init)
		SendInformation(InformationType::IT_ERROR, std::string("ErrorManager tried to be initialized twize"));
	
	game = game;
	logPath = "../Log.html";
	std::string msg = "";
	ResourceManager::WriteFile(logPath, msg, true);

	init = true;
	ErrorManager::SendInformation(InformationType::IT_INFO, std::string("ErrorManager initialized"));
}

void ErrorManager::ShutDown() {
	if (init) {
		SendInformation(InformationType::IT_INFO, std::string("ErrorManager shut down"));
		init = false;
	}
	else
		SendInformation(InformationType::IT_ERROR, std::string("ErrorManager tried to be shut down while not being initialized"));
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
