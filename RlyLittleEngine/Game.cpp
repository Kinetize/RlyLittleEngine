#include "Game.h"

Game::Game(const std::string title, int width, int height, int fps) :
	_window(Window(width, height, "Little")),
	_renderingEngine(RenderingEngine()),
	_root(GameObject()),
	_run(false),
	_timePerFrame(1.0 / (fps - 1)) //weird
{
}


Game::~Game() {

}

void Game::start() {
	ErrorManager::Init();
	_renderingEngine.Init(&_root);
	Sprite sprite(Vector2f(-1, -1), Vector2f(2, 2));
	_root.AddChildren(&sprite);

	Shader shader;

	_run = true;

	std::string msg = "Everything was loaded, Game will run";
	ErrorManager::SendInformation(InformationType::IT_INFO, msg);

	Run();
}

void Game::Run() {
	double lastTime = GetTickCount() / 1000.0;
	double unprocessedTime = 0;     
	int frames = 0;
	double frameCounter = 0;

	while (_run)
	{
		bool needToRender = false;

		double startTime = GetTickCount() / 1000.0;
		double timeDif = startTime -lastTime;
		lastTime = startTime;

		unprocessedTime += timeDif;
		frameCounter += timeDif;

		if (frameCounter >= 1.0) {
			double totalTime = ((1000.0 * frameCounter) / ((double)frames));

			std::cout << frames << std::endl;

			frames = 0;
			frameCounter = 0;
		}
		
		while (unprocessedTime > _timePerFrame) {
			_window.UpdateInputs();
			_root.UpdateAll(_timePerFrame);

			if (_window.GetCloseRequested()) {
				std::string msg = "Game stopped running without any errors";
				ErrorManager::SendInformation(InformationType::IT_INFO, msg);

				Stop();
			}

			needToRender = true;
			unprocessedTime -= _timePerFrame;
		}

		if (needToRender) {
			_renderingEngine.Render();

			_window.SwapBuffers();
			//SDL_GL_SwapWindow(_window->GetSDLWindow());

			frames++;
		}
		else
			Util::Delay(1);
	}
}

void Game::Stop() {
	_run = false;

	SDL_Quit();
}