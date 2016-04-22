#include "Game.h"

Game::Game(const std::string title, int width, int height, int fps) :
	_window(Window(width, height, "Little")),
	_renderingEngine(RenderingEngine()),
	_root(GameObject()),
	_run(false),
	_timePerFrame(1.0f / fps) //weird fps
{
}

Game::~Game() {
	if (_run)
		Stop(InformationType::IT_FATALERROR);
}

void Game::Start() {
	ErrorManager::Init(this);
	ResourceManager::Init();
	_renderingEngine.Init(&_root);
	Sprite sprite(Vector2f(-0.5f, -0.5f), Vector2f(0.5f, 0.5f), DEPTH_LEVEL::DL_3);
	_root.AddChildren(&sprite);
	Sprite sprite2(Vector2f(0, 0), Vector2f(0.2f, 0.35f), DEPTH_LEVEL::DL_2, 45.0f, std::string("test2.png"));
	_root.AddChildren(&sprite2);

	_run = true;
	
	ErrorManager::SendInformation(InformationType::IT_INFO, std::string("Everything was loaded, Game will run"));

	Run();
}

void Game::Stop(InformationType type) {
	_run = false;

	_renderingEngine.ShutDown();
	ResourceManager::ShutDown();
	std::string inf;
	if (type == InformationType::IT_INFO) {
		inf = "Game stopped running without any Errors";
		ErrorManager::SendInformation(type, inf);
	}
	else {
		inf = "Game stopped running after an Error";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}
	ErrorManager::ShutDown();

	SDL_Quit();
}

void Game::Run() {
	double lastTime = GetTickCount64() / 1000.0;
	double timeToProcess = 0;     
	int frames = 0;
	double frameCount = 0;

	while (_run)
	{
		bool needToRender = false;

		double startTime = GetTickCount64() / 1000.0;
		double timeDif = startTime -lastTime;
		lastTime = startTime;

		timeToProcess += timeDif;
		frameCount += timeDif;

		if (frameCount >= 1.0) {
			double totalTime = ((1000.0 * frameCount) / ((double)frames));

			std::cout << frames << std::endl;

			frames = 0;
			frameCount = 0;
		}
		
		while (timeToProcess > _timePerFrame) {
			_window.UpdateInputs();
			_root.UpdateAll(_timePerFrame);

			needToRender = true;
			timeToProcess -= _timePerFrame;

			if (_window.GetCloseRequested()) {
				needToRender = false;
				Stop(InformationType::IT_INFO);
			}
		}

		if (needToRender) {
			_renderingEngine.Render();

			_window.SwapBuffers();

			frames++;
		}
		else if(_run)
			Util::Delay(1);
	}
}