#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <SFML/Graphics.hpp>

namespace GameData {

	const std::string TAG_ENEMY = "enemy";
	const std::string TAG_BULLET = "bullet";
	const std::string TAG_PLAYER = "player";
	const std::string TAG_PARTICLE_SYSTEM = "particle_system";
	const std::string TAG_HEALING_PACK = "health";

	const std::string NAME_PLAYER = "player";
	const float PLAYER_STARTING_HEALTH = 10.0f;
	const float PLAYER_COLLISION_RADIUS = 10.0f;

	const std::string FONT_REGULAR = "Aleo-Regular.otf";
	const std::string FONT_ITALIC = "Aleo-Italic.otf";
	const std::string FONT_MONOSPACE = "monofonto.ttf";

	const std::string PATH_TO_RESOURCES = "res/";
	const std::string PATH_TO_SPRITES = "sprites/";
	const std::string PATH_TO_FONTS = "fonts/";
	const std::string PATH_TO_SOUNDS = "sounds/";
	const std::string PATH_TO_SAVE = "save.dat";

	const int DEFAULT_NUMBER_OF_ROUNDS = 5;

	const std::string SOUND_EXPLOSION_LONG = "explosion_long.ogg";
	const std::string SOUND_EXPLOSION_SHORT = "explosion_short.ogg";
	const std::string SOUND_PLAYER_SHOOT = "player_shoot.ogg";
	const std::string SOUND_ENEMY_SHOOT = "enemy_shoot.ogg";
	const std::string SOUND_MENU_CLICK = "menu_click.ogg";

	const sf::Vector2i WINDOW_SIZE = sf::Vector2i(1024, 768);
	const sf::IntRect DEFAULT_BOUNDS = sf::IntRect({ 0,0 }, WINDOW_SIZE);;
}

#endif