#include "Window.h"

Window::Window(int width, int height, const std::string& title) :
	_width(width),
	_height(height),
	_title(title),
	_input(this),
	_closeRequested(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	_glContext = SDL_GL_CreateContext(_window);

	if (!_window)
		ErrorManager::SendInformation(InformationType::IT_FATALERROR, std::string("Window could not be created"));

	//glewExperimental = GL_TRUE;

	GLenum res = glewInit();
	if (res != GLEW_OK)
		ErrorManager::SendInformation(InformationType::IT_FATALERROR, std::string("OpenGL could not be initialized"));
}

Window::~Window() {
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
}

void Window::UpdateInputs() {
	for (int i = 0; i < Input::NUM_MOUSEBUTTONS; i++)
	{
		_input.SetMouseDown(i, false);
		_input.SetMouseUp(i, false);
	}

	for (int i = 0; i < Input::NUM_KEYS; i++)
	{
		_input.SetKeyDown(i, false);
		_input.SetKeyUp(i, false);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			_closeRequested = true;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			_input.SetMouseX(e.motion.x);
			_input.SetMouseY(e.motion.y);
		}

		if (e.type == SDL_KEYDOWN)
		{
			int value = e.key.keysym.scancode;

			_input.SetKey(value, true);
			_input.SetKeyDown(value, true);
		}
		if (e.type == SDL_KEYUP)
		{
			int value = e.key.keysym.scancode;

			_input.SetKey(value, false);
			_input.SetKeyUp(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = e.button.button;

			_input.SetMouse(value, true);
			_input.SetMouseDown(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			int value = e.button.button;

			_input.SetMouse(value, false);
			_input.SetMouseUp(value, true);
		}
	}
}

void Window::SwapBuffers() {
	SDL_GL_SwapWindow(_window);
}

void Window::SetFullScreen(bool value) {
	int mode = 0;
	if (value)
		mode = SDL_WINDOW_FULLSCREEN;
	else
		mode = 0;

	SDL_SetWindowFullscreen(_window, mode);
}