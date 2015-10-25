#ifndef GAME_H
#define GAME_H
#pragma once

#include "Input.h"
#include "Window.h"
#include "Sprite.h"
#include "Shader.h"
#include<iostream>
#include<Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>


class Game {
public:
	Game(const std::string title, int width = 800, int height = 600, int fps = 60);
	~Game();

	inline Window* GetWindow() const { return _window; }

	void start();

private:
	Window*			_window;
	GameObject*		_root;
	Shader*			_shader;

	std::string		_title;

	bool			_run;

	int				_screenWidth;
	int				_screenHeight;

	float			_timePerFrame;
	float			_temp;

	bool Init(Window* window, GameObject* root, Shader* shader);
	void Run();
	void Stop();

	void Render();
};

#endif

