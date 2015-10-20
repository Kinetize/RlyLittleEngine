#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SDL/SDL.h>
#include <string>
#include "Input.h"

class Window {
public:
	Window(int width, int height, const std::string& title);
	virtual ~Window();

	void UpdateInputs();
	void SwapBuffers();

	inline bool GetCloseRequested()         const { return _closeRequested; }
	inline int GetWidth()                   const { return _width; }
	inline int GetHeight()                  const { return _height; }
	inline const std::string& GetTitle()    const { return _title; }
	inline SDL_Window* GetSDLWindow()			  { return _window; }

	void SetFullScreen(bool value);
protected:
private:
	int           _width;
	int           _height;
	std::string   _title;
	SDL_Window*   _window;
	SDL_GLContext _glContext;
	Input         _input;
	bool          _closeRequested;
};

#endif