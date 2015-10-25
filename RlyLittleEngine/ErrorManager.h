#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H
#pragma once

#include <string>

enum InformationType {

};

class ErrorManager
{
public:
	ErrorManager();
	~ErrorManager();

	void writeToLog(InformationType type, std::string& text) const;
};



#endif