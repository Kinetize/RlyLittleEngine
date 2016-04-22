#include "ResourceManager.h" 
#include <iostream> //temp

std::unordered_map<resource_key, ShaderUtil> ShaderUtil::utils = std::unordered_map<resource_key, ShaderUtil>();

bool ResourceManager::live = false;

template resource_key ResourceManager::UseResource<Shader>(const std::string& fileDir);
template resource_key ResourceManager::UseResource<Mesh>(const std::string& fileDir);
template resource_key ResourceManager::UseResource<Texture>(const std::string& fileDir);

const resource_key ResourceManager::resource_key_null = - 1;

std::unordered_map<resource_key, ResourceTupel> ResourceManager::resources = std::unordered_map<resource_key, ResourceTupel>();
std::vector<std::string> ResourceManager::openFiles = std::vector<std::string>();
resource_key ResourceManager::nextKey = -1;

GLuint ShaderUtil::Init(const std::string& fileDir, resource_key key) {
	GLuint vId, fId;

	_id = glCreateProgram();
	vId = glCreateShader(GL_VERTEX_SHADER);
	fId = glCreateShader(GL_FRAGMENT_SHADER);

	if (!_id | !vId || !fId)
		return -1;

	//relativ paths... temp
	std::string dir = "../res/shaders/" + fileDir;
	Compile(dir + ".vs", vId);
	Compile(dir + ".fs", fId);

	AddAttribute("pos");
	AddAttribute("texCoord");

	Link(vId, fId);
	//AddUniform("transform");

	utils.insert(std::make_pair(key, *this));

	return _id;
}

void ShaderUtil::Compile(const std::string& fileDir, GLuint& id) {
	std::string content = ResourceManager::ReadFile(fileDir);
	const char* contentPtr = content.c_str(); //Dirty...
	glShaderSource(id, 1, &contentPtr, nullptr);

	glCompileShader(id);

	GLint sucess = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {//Error Log etc
		GLint logSize = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);

		std::vector<GLchar> errorLog(logSize);
		glGetShaderInfoLog(id, logSize, &logSize, &errorLog[0]);
		std::string log(errorLog.begin(), errorLog.end());
		std::cout << "couldnt compile shader: " << fileDir << std::endl;
		std::cout << log << std::endl;

		glDeleteShader(id);
		return;
	}
}

void ShaderUtil::Link(const GLuint& vId, const GLuint& fId) {
	glAttachShader(_id, vId);
	glAttachShader(_id, fId);

	glLinkProgram(_id);

	GLint linked = 0;
	glGetProgramiv(_id, GL_LINK_STATUS, &linked);

	if (!linked) {
		glDeleteProgram(_id);
		glDeleteShader(vId);
		glDeleteShader(fId);
		std::cout << "couldnt link shader" << std::endl;
		return;
	}

	glDetachShader(_id, vId);
	glDetachShader(_id, fId);
	glDeleteShader(vId);
	glDeleteShader(fId);
}

void ShaderUtil::AddAttribute(const std::string& attribName) {
	if (!_id)
		return;

	glBindAttribLocation(_id, _attribCount++, attribName.c_str());
}

void ShaderUtil::AddUniform(const std::string& name) {
	GLuint uniformId = glGetUniformLocation(_id, name.c_str());

	if (uniformId == GL_INVALID_VALUE || uniformId == GL_INVALID_OPERATION)
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string("Failed to find uniform: " + name + ". Id: " + std::to_string(_id)));
	else 
		_uniforms.insert(std::make_pair(name, uniformId));
}

template<>
GLuint ResourceLoader::LoadResource<Shader>(const std::string& fileDir) {
	return ShaderUtil().Init(fileDir, ResourceManager::GetActKey());
}

template<>
GLuint ResourceLoader::LoadResource<Mesh>(const std::string& fileDir) {
	
	GLuint id = 0;

	glGenBuffers(1, &id);

	Vector2f _pos(-1, -1);
	Vector2f _dimensions(2, 2);

	//TEMP
	/*Vertex Struct nur temporär da unschön in momentaner form */Vertex vertexData[6]; //Konstanten...
	vertexData[0].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[0].pos.SetY(_pos.GetY() + _dimensions.GetY());
	vertexData[1].pos.SetX(_pos.GetX());
	vertexData[1].pos.SetY(_pos.GetY() + _dimensions.GetY());
	vertexData[2].pos.SetX(_pos.GetX());
	vertexData[2].pos.SetY(_pos.GetY());

	vertexData[3].pos.SetX(_pos.GetX());
	vertexData[3].pos.SetY(_pos.GetY());
	vertexData[4].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[4].pos.SetY(_pos.GetY());
	vertexData[5].pos.SetX(_pos.GetX() + _dimensions.GetX());
	vertexData[5].pos.SetY(_pos.GetY() + _dimensions.GetY());

	vertexData[0].texCoord.SetX(1.0f);
	vertexData[0].texCoord.SetY(1.0f);
	vertexData[1].texCoord.SetX(0.0f);
	vertexData[1].texCoord.SetY(1.0f);
	vertexData[2].texCoord.SetX(0.0f);
	vertexData[2].texCoord.SetY(0.0f);

	vertexData[3].texCoord.SetX(0.0f);
	vertexData[3].texCoord.SetY(0.0f);
	vertexData[4].texCoord.SetX(1.0f);
	vertexData[4].texCoord.SetY(0.0f);
	vertexData[5].texCoord.SetX(1.0f);
	vertexData[5].texCoord.SetY(1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //Static für den Moment...
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return id;
}

template<>
GLuint ResourceLoader::LoadResource<Texture>(const std::string& fileDir) {
	unsigned long width, height;
	std::vector<unsigned char> data;

	LoadPNGTexture(fileDir, width, height, data);

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, NULL);

	return id;
}

void ResourceLoader::LoadPNGTexture(const std::string& fileDir, unsigned long& width,
	unsigned long& height, std::vector<unsigned char>& data) { //nicht zufrieden mit Aufteilung
	std::vector<unsigned char> inData;
	
	std::string dir = "../res/textures/" + fileDir; //relativ paths...
	if (!ResourceManager::ReadFile(dir, inData))
		std::cout << "texfile error" << std::endl;

	if (decodePNG(data, width, height, &inData[0], inData.size()) != 0)
		std::cout << "pico error " << std::endl;
}

void ResourceManager::Init() {
	if (!live) {
		live = true;
		ErrorManager::SendInformation(InformationType::IT_INFO, std::string("ResourceManager initialized"));
	}
	else 
		ErrorManager::SendInformation(InformationType::IT_INFO, std::string("ResourceManager tried to be initialized twice"));
}

void ResourceManager::ShutDown() {
	if (live) {
		live = false; 
		for (auto& element : Util::GetKeysFromMap<resource_key, ResourceTupel>(resources)) 
			for (int i = resources[element].users; i > 0; i--)
				UnuseResource(element);
		
		nextKey = 0;
		ErrorManager::SendInformation(InformationType::IT_INFO, std::string("ResourceManager was shut down"));
	}
	else
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string("ResourceManager tried to be shut down while it was not initialized"));

}

bool ResourceManager::ReadFile(const std::string& fileDir, std::vector<unsigned char>& content) {//Nur momentan public...
	/*if (!live) {
		std::string inf = "ResourceManager called while not being initialized";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}*/

	std::ifstream file(fileDir, std::ios::binary);

	if (!file)
		return false;

	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(0, std::ios::beg);
	size -= file.tellg();

	content.resize(size);
	file.read((char *)&(content[0]), size);

	file.close();

	return true;
}

std::string ResourceManager::ReadFile(const std::string& fileDir) { //Unschöne, temporäre Methode, Nur momentan public...
	/*if (!live) {
		std::string inf = "ResourceManager called while not being initialized";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}*/

	std::ifstream file(fileDir);

	if (!file)
		return "";

	std::string content = "";
	std::string line;

	while (std::getline(file, line)) {
		content += line + "\n";
	}

	file.close();

	return content;
}

bool ResourceManager::WriteFile(const std::string& fileDir, const std::string& text, bool clearFile) {
	/*if (!live) {
		std::string inf = "ResourceManager called while not being initialized";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}*/
	
	std::fstream file;
	
	if(clearFile)
		file = std::fstream(fileDir, std::ios::out | std::ios::trunc);
	else
		file = std::fstream(fileDir, std::ios::out | std::ios::app);

	if (!file)
		return false;

	file << std::endl << text;

	file.close();

	return true;
}

template<class T>
resource_key ResourceManager::UseResource(const std::string& fileDir) {
	if (!live)
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string(
			"ResourceManager called while not being initialized (UseResource: " + fileDir + ")"));

	resource_key key = ResInMap(fileDir);
	
	if (key != resource_key_null) {
		resources[key].users++;
		ErrorManager::SendInformation(InformationType::IT_INFO, std::string("Resource: " + fileDir + " (id: " + std::to_string(key) + ") " +
			"has been added a user. Usercount: " + std::to_string(resources[key].users)));
		return key;
	}
	
	resources.insert(std::make_pair(++nextKey, ResourceTupel()));//Uniforms noch je nach Shader etc

	resources[nextKey].users = 1;
	resources[nextKey].fileDir = fileDir;
	//Wen id nicht valid, resource tupel nicht erstellen bzw löschen, log etc
	//resources[nextKey].resource = T(ResourceLoader::LoadResource<T>(fileDir));
	resources[nextKey].resource = std::make_unique<T>(ResourceLoader::LoadResource<T>(fileDir));

	ErrorManager::SendInformation(InformationType::IT_INFO, std::string("Resource: " + fileDir + " (id: " + std::to_string(nextKey) + ") " + "has been loaded."));

	return nextKey;
}

void ResourceManager::UnuseResource(const resource_key key) {
	if (ResInMap(key)) 
		if (--resources[key].users < 1) {
			CallResource(key, FunctionCall::F_DELETE);
			ShaderUtil::DeleteUtil(key);
			resources.erase(key);
			ErrorManager::SendInformation(InformationType::IT_INFO, std::string("Resource-id: " + std::to_string(key) + " has been unloaded."));
		}
		else
			ErrorManager::SendInformation(InformationType::IT_INFO, std::string("Resource-id: " + std::to_string(key) + " has been removed a user. " +
				"UserCount: " + std::to_string(resources[key].users)));
}

void ResourceManager::CallResource(const resource_key key, const FunctionCall func) {//Mäh
	if (!live && func != FunctionCall::F_DELETE)
		ErrorManager::SendInformation(InformationType::IT_ERROR, std::string(
			"ResourceManager called while not being initialized (CallResource Func: " + std::to_string(func) + ")"));

	if (ResInMap(key)) {
		switch (func) {
		case FunctionCall::F_INIT:
			resources[key].resource->Init();
			break;

		case FunctionCall::F_DELETE:
			resources[key].resource->Delete();
			break;

		case FunctionCall::F_BIND:
			resources[key].resource->Bind();
			break;

		case FunctionCall::F_UNBIND:
			resources[key].resource->Unbind();
			break;
		}
	}
	else
		return;
}

resource_key ResourceManager::ResInMap(const std::string& text) {
	for (auto& element : resources)
		if (element.second.fileDir.compare(text) == 0)
			return element.first;

	return resource_key_null;
}

bool ResourceManager::ResInMap(const resource_key key) {
	for (auto& element : resources)
		if (element.first == key)
			return true;

	return false;
}