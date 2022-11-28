#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char* fileName)
{
	string filePath = "images/";
	filePath += fileName;
	filePath += ".png";

	textures[fileName].loadFromFile(filePath);
}

sf::Texture& TextureManager::GetTexture(const char* key)
{
	if (textures.find(key) == textures.end()) { 
		LoadTexture(key); 
	}

	return textures[key]; 
}

void TextureManager::Clear()
{
	textures.clear();
}
