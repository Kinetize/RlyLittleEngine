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
	Sprite sprite(Vector2f(-1, -1), Vector2f(2, 2), DEPTH_LEVEL::DL_3);
	_root.AddChildren(&sprite);

	_run = true;
	
	std::string msg = "Everything was loaded, Game will run";
	ErrorManager::SendInformation(InformationType::IT_INFO, msg);

	Matrix2i a, b, c;

	a.MakeIdentity();
	b.MakeIdentity();

	Vector2f x, y;

	x.Dot(y);

	Vector2f d(1, 2);
	Vector2f e(3, 0);
	Vector2f f;

	f = d + e;
	std::cout << f.ToString() << std::endl;

	//c = a * b;

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
			_root.UpdateAll(_timePerFrame);

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