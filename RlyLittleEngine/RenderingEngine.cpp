#include "RenderingEngine.h"


RenderingEngine::RenderingEngine() :
	_init(false),
	_root(nullptr),
	_shaders(std::vector<resource_key>()),
	_baseMesh(ResourceManager::resource_key_null),
	_baseTexture(ResourceManager::resource_key_null)
{
}


RenderingEngine::~RenderingEngine() {
	//Löschen...
	for (auto & element : _shaders)
		ResourceManager::UnuseResource(element);

	ResourceManager::UnuseResource(_baseMesh);
	ResourceManager::UnuseResource(_baseTexture);
}

void RenderingEngine::Init(GameObject* root) {
	if (_init) {
		std::string inf = "RenderingEngine tried to be initialized twize";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}
	
	_init = true;
	_root = root;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	SDL_GL_SetSwapInterval(1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	std::string test = "test.png";
	_baseTexture = ResourceManager::UseResource<Texture>(test);
	std::string dir = "baseShader";
	_shaders.push_back(ResourceManager::UseResource<Shader>(dir));
	dir = "baseMesh";
	_baseMesh = ResourceManager::UseResource<Mesh>(dir);

	std::string inf = "RenderingEngine initialized";
	ErrorManager::SendInformation(InformationType::IT_INFO, inf);
}

void RenderingEngine::ShutDown() {
	if (!_init) {
		std::string inf = "RenderingEngine tried to be shut down twice";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}
	else {
		_init = false;
		std::string inf = "RenderingEngine was shut down";
		ErrorManager::SendInformation(InformationType::IT_INFO, inf);
	}
}

void RenderingEngine::Render() const {
	if (!_init) {
		std::string inf = "RenderingEngine called to render while not being initialized";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (auto& element : _shaders) {
		//Shader temps = Shader(1);
		//element->Bind();
		//TODO: Kopierkonstruktoren überall, kovertierung von resourcen, math header, mehr funktionen in vektoren etc
		//TEMP
		//Mesh tempm = Mesh(1);
		//Texture tempt = Texture(1);
		ResourceManager::CallResource(element, FunctionCall::F_BIND);

		ResourceManager::CallResource(_baseTexture, FunctionCall::F_BIND);
		_root->RenderAll(element, _baseMesh, DL_3, Area());
		_root->RenderAll(element, _baseMesh, DL_2, Area());
		_root->RenderAll(element, _baseMesh, DL_1, Area());
		_root->RenderAll(element, _baseMesh, DL_0, Area());

		ResourceManager::CallResource(element, FunctionCall::F_UNBIND);
	}
}
