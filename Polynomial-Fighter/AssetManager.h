#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameData.h"
#include <unordered_map>
#include <memory>

class Assets
{
public:
	static const std::string FONT_REGULAR;
	static const std::string FONT_ITALIC;
	static const std::string FONT_MONOSPACE;
	static const std::string FONT_LATO;

	static const std::string PATH_TO_RESOURCES;
	static const std::string PATH_TO_IMAGES;
	static const std::string PATH_TO_HOW_TO;
	static const std::string PATH_TO_FONTS;
	static const std::string PATH_TO_SOUNDS;
	static const std::string PATH_TO_SAVE;
	static const std::string PATH_TO_COLOR_SCHEME;

	static const std::string ICON;

	static const std::string SOUND_ADD_ROUNDS;
	static const std::string SOUND_DIV_0;
	static const std::string SOUND_ENEMY_HIT;
	static const unsigned SOUND_ENEMY_HIT_REPLACE;
	static const std::string SOUND_ENEMY_SHOOT;
	static const unsigned SOUND_ENEMY_SHOOT_REPLACE;
	static const std::string SOUND_FAILED; //todo
	static const std::string SOUND_MENU_BACK;
	static const std::string SOUND_CLICK;
	static const std::string SOUND_EXIT;
	static const std::string SOUND_NO_ROUNDS;
	static const std::string SOUND_PAUSE;
	static const std::string SOUND_PLAYER_HIT;
	static const int SOUND_PLAYER_HIT_REPLACE;
	static const std::string SOUND_PLAYER_SHOOT;
	static const std::string SOUND_SOUND_ON;
	static const std::string SOUND_WAVE;
	static const std::string SOUND_EXPLOSION_LONG;
	static const std::string SOUND_EXPLOSION_SHORT;
	static const std::string SOUND_GAME_LOAD;
	static const std::string SOUND_ROLLING_LIST_MOVE;
	static const std::string SOUND_MISS;
	static const std::string SOUND_MENU_LOAD;
};

class AssetManager
{
public:
	using TexturePointer = std::shared_ptr <sf::Texture>;
	using FontPointer = std::shared_ptr<sf::Font>;
	using SoundBufferPointer = std::shared_ptr<sf::SoundBuffer>;
private:
	AssetManager() = default;

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