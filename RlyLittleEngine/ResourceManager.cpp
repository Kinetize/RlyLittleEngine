#include "ResourceManager.h" 
#include <iostream> //temp

template void ResourceManager::UnuseResource<Texture>(Texture* resource);

std::vector<Resource<Shader>> ResourceManager::_shaders = std::vector<Resource<Shader>>();
std::vector<Resource<Mesh>> ResourceManager::_meshes = std::vector<Resource<Mesh>>();
std::vector<Resource<Texture>> ResourceManager::_textures = std::vector<Resource<Texture>>();

bool ResourceManager::ReadFile(std::string& fileDir, std::vector<unsigned char>& content) {//Nur momentan public...
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

std::string ResourceManager::ReadFile(std::string fileDir) { //Unschöne, temporäre Methode, Nur momentan public...
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

bool ResourceManager::WriteFile(std::string& fileDir, std::string& text, bool clearFile) {
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
T* ResourceManager::UseResource(std::string& fileDir) {
	int index = ResInVector<T>(fileDir);
	std::vector<Resource<T>>* vector = GetSuitableVector<T>();

	if (index > -1) {
		(*vector)[index].users++;
		return &(*vector)[index].resource;
	}

	(*vector).push_back(Resource<T>());//Uniforms noch je nach Shader etc

	(*vector)[(*vector).size() - 1].users = 1;
	(*vector)[(*vector).size() - 1].fileDir = fileDir;

	InitResource<T>();
	_shaders[_shaders.size() - 1].resource.Compile("C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/shaders/baseShader"); //relativ paths, filedir
	_shaders[_shaders.size() - 1].resource.AddAttribute("pos");
	_shaders[_shaders.size() - 1].resource.AddAttribute("texCoord");
	_shaders[_shaders.size() - 1].resource.Link();

	return &(*vector)[(*vector).size() - 1].resource;
}

template<>
void ResourceManager::InitResource<Shader>() {
	_shaders[_shaders.size() - 1].resource.Compile("C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/shaders/baseShader"); //relativ paths, filedir
	_shaders[_shaders.size() - 1].resource.AddAttribute("pos");
	_shaders[_shaders.size() - 1].resource.AddAttribute("texCoord");
	_shaders[_shaders.size() - 1].resource.Link();
}

template<>
void ResourceManager::InitResource<Mesh>() {
	//richtig laden...
	_meshes[_meshes.size() - 1].resource = Mesh();

	glGenBuffers(1, _meshes[_meshes.size() - 1].resource.GetIDPTR());

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

	glBindBuffer(GL_ARRAY_BUFFER, _meshes[_meshes.size() - 1].resource.GetID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //Static für den Moment...
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<>
void ResourceManager::InitResource<Texture>() {
	//if(fileDir.size() > 3 && fileDir.substr(fileDir.size() - 4, fileDir.size() - 1).compare(".png")) //eig bei "." splitten
	LoadPNGTexture(_textures[_textures.size() - 1].fileDir);
	//else
	//	return LoadPNGTexture(fileDir); //Eigentlich Fehlermeldung, anderer Dateityp o.ä.
}

template<class T>
void ResourceManager::UnuseResource(T* resource) {
	int index = ResInVector<T>(resource);
	std::vector<Resource<T>>* vector = GetSuitableVector<T>();

	if (index > -1) {
		if (--(*vector)[index].users < 1) {
			(*vector)[index].resource.Delete();
			//Element löschen, Texure ausm Speicher kicken, Vector auffüllen etc
		}
	}
}

template<class T>
int ResourceManager::ResInVector(std::string& text) {

	int index = -1;

	for (auto& element : *GetSuitableVector<T>()) {
		index++;

		if (element.fileDir.compare(text) == 0)
			return index;
	}

	return -1;
}

template<class T>
int ResourceManager::ResInVector(T* resource) {

	int index = -1;

	for (auto& element : *GetSuitableVector<T>()) {
		index++;

		if (element.resource.GetID() == resource->GetID())
			return index;
	}

	return -1;
}

template<> 
std::vector<Resource<Shader>>* ResourceManager::GetSuitableVector<Shader>() {
	return &_shaders;
}

template<>
std::vector<Resource<Mesh>>* ResourceManager::GetSuitableVector<Mesh>() {
	return &_meshes;
}

template<>
std::vector<Resource<Texture>>* ResourceManager::GetSuitableVector<Texture>() {
	return &_textures;
}

void ResourceManager::LoadPNGTexture(std::string& fileDir) { //nicht zufrieden mit Aufteilung
	std::vector<unsigned char> inData, outData;
	unsigned long width, height;
	std::string dir = "C:/Users/Nils/Documents/Visual Studio 2015/Projects/RlyLittleEngine/res/textures/" + fileDir; //relativ paths...
	if (!ReadFile(dir, inData))
		std::cout << "texfile error" << std::endl;

	if (decodePNG(outData, width, height, &inData[0], inData.size()) != 0)
		std::cout << "pico error " << std::endl;

	_textures.push_back(Resource<Texture>());
	_textures[_textures.size() - 1].fileDir = fileDir;
	_textures[_textures.size() - 1].resource.Init(width, height, outData);
	_textures[_textures.size() - 1].users = 1;
}