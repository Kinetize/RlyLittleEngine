#include "RenderingEngine.h"


RenderingEngine::RenderingEngine() :
	_init(false),
	_root(nullptr),
	_shaders(std::unordered_map<resource_key, ShaderType>()),
	_baseMesh(ResourceManager::resource_key_null),
	_baseTexture(ResourceManager::resource_key_null)
{
}


RenderingEngine::~RenderingEngine() {
	//L�schen...
	for (auto & element : _shaders)
		ResourceManager::UnuseResource(element.first);

	ResourceManager::UnuseResource(_baseMesh);
	ResourceManager::UnuseResource(_baseTexture);
}

void RenderingEngine::Init(GameObject* root) {
	if (_init)
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string("RenderingEngine tried to be initialized twize"));
	
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

	_baseTexture = ResourceManager::UseResource<Texture>(std::string("test.png"));
	//_shaders.insert(std::make_pair(ResourceManager::UseResource<Shader>(std::string("baseShader")), ShaderType::ST_BASE));
	_shaders.insert(std::make_pair(ResourceManager::UseResource<Shader>(std::string("ambientShader")), ShaderType::ST_AMBIENT));
	_shaders.insert(std::make_pair(ResourceManager::UseResource<Shader>(std::string("directionalShader")), ShaderType::ST_AMBIENT));
	_baseMesh = ResourceManager::UseResource<Mesh>(std::string("baseMesh"));

	for (auto& element : _shaders) {//MIT STRUCT IN SHADERN ARBEITEN
		ShaderUtil::GetUtil(element.first).AddUniform("transform");
		if(element.second == ShaderType::ST_AMBIENT)
			ShaderUtil::GetUtil(element.first).AddUniform("ambientLight");
		else if (element.second == ShaderType::ST_POINT) {
			ShaderUtil::GetUtil(element.first).AddUniform("lightPos");
			ShaderUtil::GetUtil(element.first).AddUniform("lightStrenght");
			ShaderUtil::GetUtil(element.first).AddUniform("lightAttributes");
		}
	}

	ErrorManager::SendInformation(InformationType::IT_INFO, std::string("RenderingEngine initialized"));
}

void RenderingEngine::ShutDown() {
	if (!_init)
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string("RenderingEngine tried to be shut down twice"));
	else {
		_init = false;
		ErrorManager::SendInformation(InformationType::IT_INFO, std::string("RenderingEngine was shut down"));
	}
}

void RenderingEngine::Render() const {
	if (!_init)
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string("RenderingEngine called to render while not being initialized"));

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Get all Lights

	for (auto& element : _shaders) {
		//Shader temps = Shader(1);
		//element->Bind();
		//TODO: Kopierkonstruktoren �berall, kovertierung von resourcen, math header, mehr funktionen in vektoren etc
		//TEMP
		//Mesh tempm = Mesh(1);
		//Texture tempt = Texture(1);
		ResourceManager::CallResource(element.first, FunctionCall::F_BIND);
		if (element.second == ShaderType::ST_AMBIENT)
			ShaderUtil::GetUtil(element.first).SetUniformV3f(std::string("ambientLight"), Vector3f(0.2f, 1.0f, 0.5f));

		ResourceManager::CallResource(_baseTexture, FunctionCall::F_BIND);
		_root->RenderAll(element.first, _baseMesh, DL_3, Area());
		_root->RenderAll(element.first, _baseMesh, DL_2, Area());
		_root->RenderAll(element.first, _baseMesh, DL_1, Area());
		_root->RenderAll(element.first, _baseMesh, DL_0, Area());

		ResourceManager::CallResource(element.first, FunctionCall::F_UNBIND);
	}
}
