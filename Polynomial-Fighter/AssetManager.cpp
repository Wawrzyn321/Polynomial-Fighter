#include "Asset Manager.h"
#include <assert.h>
#include <iostream>

AssetManager *AssetManager::sInstance = NULL;


AssetManager * AssetManager::instance()
{
	if (sInstance == NULL) {
		sInstance = new AssetManager();
	}
	return sInstance;
}

sf::Texture *AssetManager::getTexture(const std::string &filename){
    auto &texMap = sInstance->textures;
    auto pairFound = texMap.find(filename);
    if (pairFound != texMap.end())
        return &(pairFound->second);
    else{
        sf::Texture &texture = texMap[filename];
        
        if (!texture.loadFromFile(filename)){
			Debug::PrintErrorFormatted("AssetManager::getTexture: cannot texture sound %!", filename);
			system("pause");
			exit(-1); //todo
        }
        return &texture;
    }
}

sf::Font *AssetManager::getFont(const std::string &filename){
    auto &sFontMap = sInstance->fonts;
    auto pairFound = sFontMap.find(filename);
	if (pairFound != sFontMap.end()) {
		return &(pairFound->second);
	}
    else {
		sf::Font &sFont = sFontMap[filename];
        if (!sFont.loadFromFile(filename)){
			Debug::PrintErrorFormatted("AssetManager::getFont: cannot load font %!", filename);
			system("pause");
        }
        return &sFont;
    }
}

sf::SoundBuffer * AssetManager::getSound(const std::string & filename)
{
	auto &sSoundMap = sInstance->sounds;
	auto pairFound = sounds.find(filename);
	if (pairFound != sSoundMap.end()) {
		return &(pairFound->second);
	}
	else {
		sf::SoundBuffer &sSound = sSoundMap[filename];
		if (!sSound.loadFromFile(filename)) {
			Debug::PrintErrorFormatted("AssetManager::getSound: cannot load sound %!", filename);
			system("pause");
		}
		return &sSound;
	}
}
