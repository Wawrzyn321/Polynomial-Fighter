#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include "Debug.h"

class AssetManager
{
private:
	AssetManager() = default;
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
    static AssetManager* sInstance;

public:
    static AssetManager *instance();

	std::shared_ptr<sf::Texture> getTexture(const std::string &filename);
	std::shared_ptr<sf::Font> getFont(const std::string &filename);
	std::shared_ptr<sf::SoundBuffer> getSound(const std::string &filename);
};


#endif