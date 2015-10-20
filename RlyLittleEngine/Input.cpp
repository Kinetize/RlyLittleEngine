#include "Input.h"
#include "Window.h"
#include <SDL/SDL.h>
#include <cstring>

Input::Input(Window* window) :
	_mouseX(0),
	_mouseY(0),
	_window(window)
{
	memset(_inputs, 0, NUM_KEYS * sizeof(bool));
	memset(_downKeys, 0, NUM_KEYS * sizeof(bool));
	memset(_upKeys, 0, NUM_KEYS * sizeof(bool));

	memset(_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
	memset(_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
}

void Input::SetCursor(bool visible) const {
	if (visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Input::SetMousePosition(const Vector2f& pos) const {
	SDL_WarpMouseInWindow(_window->GetSDLWindow(), (int)pos.GetX(), (int)pos.GetY());
}
