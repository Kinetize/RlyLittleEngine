#include "Game.h"

Game::Game(const std::string title, int width, int height, int fps) :
	_window(nullptr),
	_root(nullptr),
	_title(title),
	_run(false),
	_screenWidth(width),
	_screenHeight(height),
	_timePerFrame(1.0 / fps)
{
}


Game::~Game() {

}

void Game::start() {
	Window window(_screenWidth, _screenHeight, "Little"); //Class variable?
	GameObject root(1); //Class variable?

	/*relativ paths...*/Shader shader;
	shader.Compile("C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/shaders/baseShader");
	shader.AddAttribute("pos");
	shader.Link();
	Sprite sprite(Vector2f(-1, -1), Vector2f(1, 1));
	root.AddChildren(&sprite);

	if (Init(&window, &root, &shader))
		_run = true;
	else
		std::cerr << "Failed to Init" << std::endl;

	Run();
}

bool Game::Init(Window* window, GameObject* root, Shader* shader) { //kinda senceless
	_window = window;
	_root = root;
	_shader = shader;

	return true;
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
			_window->UpdateInputs();
			_root->UpdateAll();

			if (_window->GetCloseRequested())
				Stop();

			needToRender = true;
			unprocessedTime -= _timePerFrame;
		}

		if (needToRender) {
			Render();

			_window->SwapBuffers();
			//SDL_GL_SwapWindow(_window->GetSDLWindow());

			frames++;
		}
		else
			SDL_Delay(1);
	}
}

void Game::Stop() {
	_run = false;
	SDL_Quit();
	//TODO: Cleanup, Error-Handling etc...
}

void Game::Render() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->Bind();
	_root->RenderAll();
	_shader->Unbind();
}
