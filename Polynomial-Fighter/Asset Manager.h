#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include "Debug.h"

class AssetManager{
private:
	AssetManager() {}
    std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::SoundBuffer> sounds;
    static AssetManager* sInstance;
public:
	static AssetManager *instance();

	sf::Texture *getTexture(const std::string &filename);
	sf::Font *getFont(const std::string &filename);
	sf::SoundBuffer *getSound(const std::string &filename);


};


#endif