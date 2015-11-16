#ifndef GAME_H
#define GAME_H
#pragma once

#include "Input.h"
#include "Window.h"
#include "Sprite.h"
#include "Shader.h"
#include "ErrorManager.h"
#include "RenderingEngine.h"
#include<iostream>
#include<Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>


class Game {
public:
	Game(const std::string title, int width = 800, int height = 600, int fps = 60);
	~Game();

	inline Window GetWindow() const { return _window; }

	void start();

private://Nicht mehr überall ptr
	Window				_window;
	RenderingEngine		_renderingEngine;
	GameObject			_root;
		
	bool				_run;

	float				_timePerFrame;

	void Run();
	void Stop();
};

#endif

