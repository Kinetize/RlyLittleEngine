#include "Game.h"

Game::Game(const std::string title, int width, int height, int fps) :
	_window(nullptr),
	_root(nullptr),
	_title(title),
	_run(false),
	_screenWidth(width),
	_screenHeight(height),
	_timePerFrame(1.0 / (fps - 1)), //weird
	_temp(0),
	_tex(nullptr)
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
	shader.AddAttribute("color");
	shader.Link();
	Sprite sprite(Vector2f(-1, -1), Vector2f(2, 2));
	root.AddChildren(&sprite);

	if (Init(&window, &root, &shader))
		_run = true;
	else
		std::cerr << "Failed to Init" << std::endl;

	ErrorManager::Init();
	//Test
	//_shader->SetUniformI("gSampler", 0);
	std::string test = "test.png";
	//_tex = ResourceManager::UseTexture(test);
	_tex = ResourceManager::UseTexture(test);


	std::string msg = "Everything was loaded, Game will run";
	ErrorManager::SendInformation(InformationType::IT_INFO, msg);

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
			_root->UpdateAll(_timePerFrame);

			if (_window->GetCloseRequested()) {
				std::string msg = "Game stopped running without any errors";
				ErrorManager::SendInformation(InformationType::IT_INFO, msg);

				Stop();
			}

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
			Util::Delay(1);
	}
}

void Game::Stop() {
	_run = false;

	_tex->Delete();
	//ResourceManager::UnuseTexture(test);
	//ResourceManager::UnuseTexture(test2);

	SDL_Quit();
	//TODO: Cleanup, Error-Handling etc...
}

void Game::Render() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader->Bind();
	_tex->Bind();
	_temp += 0.02f;
	Mesh* mesh = &Mesh();
	_root->RenderAll(_shader, mesh, Area());

	_shader->Unbind();
}
