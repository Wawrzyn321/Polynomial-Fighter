#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>

class AssetManager
{
private:
	using TexturePointer = std::shared_ptr <sf::Texture>;
	using FontPointer = std::shared_ptr<sf::Font>;
	using SoundBufferPointer = std::shared_ptr<sf::SoundBuffer>;

	AssetManager() = default;
    std::map<std::string, TexturePointer> textures;
	std::map<std::string, FontPointer> fonts;
	std::map<std::string, SoundBufferPointer> sounds;
    static AssetManager* sInstance;

public:
    static AssetManager *instance();

	TexturePointer getTexture(const std::string &filename);
	FontPointer getFont(const std::string &filename);
	SoundBufferPointer getSound(const std::string &filename);
	FontPointer getDefaultFont();
};

#endif