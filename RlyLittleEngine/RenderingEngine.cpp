#include "RenderingEngine.h"

void Camera::Update(const float delta, const Input& input) {
	float x = input.GetKey(Input::KEY_RIGHT) ? -_speed * delta : (input.GetKey(Input::KEY_LEFT) ? _speed * delta : 0);
	float y = input.GetKey(Input::KEY_UP) ? -_speed * delta : (input.GetKey(Input::KEY_DOWN) ? _speed * delta : 0);
	Move(Vector2f(x, y));

	_rendEngine->SetCamTranslation(Matrix4f().MakeTranslation(Vector4f(_pos, 0, 1)));
}

RenderingEngine::RenderingEngine() :
	_init(false),
	_root(nullptr),
	_projection(Matrix4f()),
	_camTrans(Matrix4f()),
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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	_baseTexture = ResourceManager::UseResource<Texture>(std::string("test.png"));
	_shaders.push_back(ResourceManager::UseResource<Shader>(std::string("baseShader")));
	_baseMesh = ResourceManager::UseResource<Mesh>(std::string("baseMesh"));

	for (auto& element : _shaders) {
		ShaderUtil::GetUtil(element).AddUniform("transform");
	}

	//_root->AddChildren(&Camera(*this));

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
	
	for (auto& element : _shaders) {
		//Shader temps = Shader(1);
		//element->Bind();
		//TODO: Kopierkonstruktoren überall, kovertierung von resourcen, math header, mehr funktionen in vektoren etc
		//TEMP
		//Mesh tempm = Mesh(1);
		//Texture tempt = Texture(1);
		ResourceManager::CallResource(element, FunctionCall::F_BIND);
		ShaderUtil::GetUtil(element).SetProjection(_projection * _camTrans);

		ResourceManager::CallResource(_baseTexture, FunctionCall::F_BIND);
		_root->RenderAll(element, _baseMesh, DL_3, Area());
		_root->RenderAll(element, _baseMesh, DL_2, Area());
		_root->RenderAll(element, _baseMesh, DL_1, Area());
		_root->RenderAll(element, _baseMesh, DL_0, Area());

		ResourceManager::CallResource(element, FunctionCall::F_UNBIND);
	}
}