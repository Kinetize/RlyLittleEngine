#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H
#pragma once

#include <string>

enum ErrorType {

};

class ErrorManager
{
public:
	ErrorManager();
	~ErrorManager();

	void writeToLog(ErrorType type, std::string& text) const;
};



#endif