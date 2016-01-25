#include "ResourceManager.h" 
#include <iostream> //temp

bool ResourceManager::_live = false;

template resource_key ResourceManager::UseResource<Shader>(const std::string& fileDir);
template resource_key ResourceManager::UseResource<Mesh>(const std::string& fileDir);
template resource_key ResourceManager::UseResource<Texture>(const std::string& fileDir);

const resource_key ResourceManager::resource_key_null = - 1;

std::unordered_map<resource_key, ResourceTupel> ResourceManager::_resources = std::unordered_map<resource_key, ResourceTupel>();
std::vector<std::string> ResourceManager::_openFiles = std::vector<std::string>();
resource_key ResourceManager::_nextkey = -1;

template<>
GLuint ResourceLoader::LoadResource<Shader>(const std::string& fileDir) {
	GLuint id, vId, fId;
	int attribCount = 0;

	id = glCreateProgram();
	vId = glCreateShader(GL_VERTEX_SHADER);
	fId = glCreateShader(GL_FRAGMENT_SHADER);

	if (!id | !vId || !fId)
		return -1;

	//relativ paths... temp
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/shaders/baseShader";
	CompileShader(dir + ".vs", vId);
	CompileShader(dir + ".fs", fId);

	AddAttributeToShader(id, attribCount, "pos");
	AddAttributeToShader(id, attribCount, "texCoord");

	LinkShader(id, vId, fId);

	return id;
}

template<>
GLuint ResourceLoader::LoadResource<Mesh>(const std::string& fileDir) {
	
	GLuint id = 0;

	glGenBuffers(1, &id);

	Vector2f _pos(-1, -1);
	Vector2f _dimensions(2, 2);

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

void ResourceLoader::CompileShader(const std::string& fileDir, GLuint& id) {
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
		std::cout << "couldnt compile shader" << std::endl;
		std::cout << log << std::endl;

		glDeleteShader(id);
		return;
	}
}

void ResourceLoader::AddAttributeToShader(GLuint& id, int& attribCount, const std::string& attribName) {
	if (!id)
		return;

	glBindAttribLocation(id, attribCount++, attribName.c_str());
}

void ResourceLoader::LinkShader(const GLuint& id, const GLuint& vId, const GLuint& fId) {
	glAttachShader(id, vId);
	glAttachShader(id, fId);

	glLinkProgram(id);

	GLint linked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &linked);

	if (!linked) {
		glDeleteProgram(id);
		glDeleteShader(vId);
		glDeleteShader(fId);
		std::cout << "couldnt link shader" << std::endl;
		return;
	}

	glDetachShader(id, vId);
	glDetachShader(id, fId);
	glDeleteShader(vId);
	glDeleteShader(fId);
}

void ResourceLoader::LoadPNGTexture(const std::string& fileDir, unsigned long& width,
	unsigned long& height, std::vector<unsigned char>& data) { //nicht zufrieden mit Aufteilung
	std::vector<unsigned char> inData;
	
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/textures/" + fileDir; //relativ paths...
	if (!ResourceManager::ReadFile(dir, inData))
		std::cout << "texfile error" << std::endl;

	if (decodePNG(data, width, height, &inData[0], inData.size()) != 0)
		std::cout << "pico error " << std::endl;
}

void ResourceManager::Init() {
	if (!_live) {
		_live = true;
		std::string inf = "ResourceManager initialized";
		ErrorManager::SendInformation(InformationType::IT_INFO, inf);
	}
	else {
		std::string inf = "ResourceManager tried to be initialized twice";
		ErrorManager::SendInformation(InformationType::IT_INFO, inf);
	}
}

void ResourceManager::ShutDown() {
	if (_live) {
		_live = false; //Delete all pointers etc
		std::string inf = "ResourceManager was shut down";
		ErrorManager::SendInformation(InformationType::IT_INFO, inf);
	}
	else {
		std::string inf = "ResourceManager tried to be shut down while it was not initialized";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}

}

bool ResourceManager::ReadFile(const std::string& fileDir, std::vector<unsigned char>& content) {//Nur momentan public...
	/*if (!_live) {
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
	/*if (!_live) {
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
	/*if (!_live) {
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
	if (!_live) {
		std::string inf = "ResourceManager called while not being initialized (UseResource: " + fileDir + ")";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}

	resource_key key = ResInMap(fileDir);
	
	if (key != resource_key_null) {
		_resources[key].users++;
		return key;
	}
	
	_resources.insert(std::make_pair(++_nextkey, ResourceTupel()));//Uniforms noch je nach Shader etc

	_resources[_nextkey].users = 1;
	_resources[_nextkey].fileDir = fileDir;
	//Wen id nicht valid, resource tupel nicht erstellen bzw löschen, log etc
	//_resources[_nextkey].resource = T(ResourceLoader::LoadResource<T>(fileDir));
	_resources[_nextkey].resource = std::make_unique<T>(ResourceLoader::LoadResource<T>(fileDir));

	return _nextkey;
}

void ResourceManager::UnuseResource(const resource_key key) {
	if (ResInMap(key)) 
		if (--_resources[key].users < 1) 
			CallResource(key, FunctionCall::F_DELETE);
			//Element löschen, resource ausm Speicher kicken, Vector auffüllen etc
}

void ResourceManager::CallResource(const resource_key key, const FunctionCall func) {//Mäh
	if (!_live && func != FunctionCall::F_DELETE) {
		std::string inf = "ResourceManager called while not being initialized (CallResource Func: " + std::to_string(func) + ")";
		ErrorManager::SendInformation(InformationType::IT_ERROR, inf);
	}

	if (ResInMap(key)) {
		switch (func) {
		case FunctionCall::F_INIT:
			_resources[key].resource->Init();
			break;

		case FunctionCall::F_DELETE:
			_resources[key].resource->Delete();
			break;

		case FunctionCall::F_BIND:
			_resources[key].resource->Bind();
			break;

		case FunctionCall::F_UNBIND:
			_resources[key].resource->Unbind();
			break;
		}
	}
	else
		return;
}

resource_key ResourceManager::ResInMap(const std::string& text) {
	for (auto& element : _resources)
		if (element.second.fileDir.compare(text) == 0)
			return element.first;

	return resource_key_null;
}

bool ResourceManager::ResInMap(const resource_key key) {
	for (auto& element : _resources)
		if (element.first == key)
			return true;

	return false;
}