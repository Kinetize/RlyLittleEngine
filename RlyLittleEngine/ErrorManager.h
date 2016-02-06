#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <string>

enum InformationType {
	IT_INFO = 0,
	IT_ERROR = 1,
	IT_FATALERROR = 2
};

class Game;

class ErrorManager {
public:
	static void Init(Game* game);
	static void ShutDown();

	static void SendInformation(InformationType type, std::string& text);

private:
	static bool init;

	static std::string logPath; //Konstante?

	static Game* game;

	static void WriteToLog(InformationType type, std::string& text);
};

#endif