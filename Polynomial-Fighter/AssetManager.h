#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>

class AssetManager
{
private:
	AssetManager() = default;

	using TexturePointer = std::shared_ptr <sf::Texture>;
	using FontPointer = std::shared_ptr<sf::Font>;
	using SoundBufferPointer = std::shared_ptr<sf::SoundBuffer>;

    std::unordered_map<std::string, TexturePointer> textures;
	std::unordered_map<std::string, FontPointer> fonts;
	std::unordered_map<std::string, SoundBufferPointer> sounds;

    static AssetManager* sInstance;

public:
    static AssetManager *instance();

	TexturePointer getTexture(const std::string &filename);
	FontPointer getFont(const std::string &filename);
	SoundBufferPointer getSound(const std::string &filename);
	FontPointer getDefaultFont();
};

#endif