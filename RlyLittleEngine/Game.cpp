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
	_renderingEngine.CalcProjection(75, 0.1f, 1000.0f, _window.GetAspectRatio());
	Sprite sprite(Vector2f(0, 0), Vector2f(2, 1), std::string("back.png"), DEPTH_LEVEL::DL_3);
	Sprite sprite2(Vector2f(-0.2f, -0.5f), Vector2f(0.25f, 0.1f), std::string("test.png"), DEPTH_LEVEL::DL_2);
	Camera cam(_renderingEngine); //Eig in Rendering Engine initialisieren, hinnzufügen tec
	_root.AddChildren(&cam);
	_root.AddChildren(&sprite);
	_root.AddChildren(&sprite2);

	_run = true;
	
	std::string msg = "Everything was loaded, Game will run";
	ErrorManager::SendInformation(InformationType::IT_INFO, msg);

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
	double unprocessedTime = 0;     
	int frames = 0;
	double frameCounter = 0;

	while (_run)
	{
		bool needToRender = false;

		double startTime = GetTickCount64() / 1000.0;
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
			_root.UpdateAll(_timePerFrame, _window.GetInput());

			needToRender = true;
			unprocessedTime -= _timePerFrame;

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