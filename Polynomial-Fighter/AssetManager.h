#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameData.h"
#include <unordered_map>
#include <memory>

namespace Assets
{
	const std::string FONT_REGULAR = "Aleo-Regular.otf";
	const std::string FONT_ITALIC = "Aleo-Italic.otf";
	const std::string FONT_MONOSPACE = "monofonto.ttf";

	const std::string PATH_TO_RESOURCES = "res/";
	const std::string PATH_TO_IMAGES = "img/";
	const std::string PATH_TO_HOW_TO = "howto/";
	const std::string PATH_TO_FONTS = "fonts/";
	const std::string PATH_TO_SOUNDS = "sounds/";
	const std::string PATH_TO_SAVE = "save.dat";
	const std::string PATH_TO_COLOR_SCHEME = "colorScheme.dat";

	const std::string ICON = "icon.png";

	const std::string SOUND_ADD_ROUNDS = "add_rounds.ogg";
	const std::string SOUND_DIV_0 = "div0.ogg";
	const std::string SOUND_ENEMY_HIT = "enemy_hit_0X.ogg";
	const unsigned SOUND_ENEMY_HIT_REPLACE = 11;
	const std::string SOUND_ENEMY_SHOOT = "enemy_shoot_0X.ogg";
	const unsigned SOUND_ENEMY_SHOOT_REPLACE = 13;
	const std::string SOUND_FAILED = "failed.ogg"; //todo
	const std::string SOUND_MENU_BACK = "menu_back.ogg";
	const std::string SOUND_CLICK = "menu_click.ogg";
	const std::string SOUND_EXIT = "menu_exit.ogg";
	const std::string SOUND_NO_ROUNDS = "no_rounds.ogg";
	const std::string SOUND_PAUSE = "pause.ogg";
	const std::string SOUND_PLAYER_HIT = "player_hit_0X.ogg";
	const int SOUND_PLAYER_HIT_REPLACE = 12;
	const std::string SOUND_PLAYER_SHOOT = "player_shoot.ogg";
	const std::string SOUND_SOUND_ON = "sound_on.ogg";
	const std::string SOUND_WAVE = "wave.ogg";
	const std::string SOUND_EXPLOSION_LONG = "explosion_long.ogg";
	const std::string SOUND_EXPLOSION_SHORT = "explosion_short.ogg";
	const std::string SOUND_GAME_LOAD = "game_load.ogg";
	const std::string SOUND_ROLLING_LIST_MOVE = "rolling_list_move.ogg";
	const std::string SOUND_MISS = "miss.ogg";
}

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