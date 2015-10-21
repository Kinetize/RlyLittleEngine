#include "Texture.h"



Texture::Texture(const std::string& fileDir) { //.../res/textures mit rein nehmen 
	loadTexture(fileDir);
}

void Texture::Update() {

}

void Texture::Render() const {

}

bool Texture::loadTexture(const std::string& fileDir) {

	return true;
}

