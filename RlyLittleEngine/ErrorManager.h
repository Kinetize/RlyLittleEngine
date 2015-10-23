#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H
#pragma once

class ErrorManager
{
public:
	ErrorManager();
	~ErrorManager();

	void writeToLog() const;
};

#endif