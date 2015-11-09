#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H
#pragma once

#include "ResourceManager.h"

enum InformationType {
	IT_INFO = 0,
	IT_ERROR = 1,
	IT_FATALERROR = 2
};

class ErrorManager {
public:
	static void Init();

	static void SendInformation(InformationType type, std::string& text);

private:
	static bool init;

	static void WriteToLog(InformationType type, std::string& text);
};



#endif