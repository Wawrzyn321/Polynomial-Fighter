#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <SFML/Graphics.hpp>

namespace GameData {


	const std::string TAG_ENEMY = "enemy";
	const std::string TAG_PLAYER_BULLET = "player_bullet";
	const std::string TAG_ENEMY_BULLET = "enemy_bullet";
	const std::string TAG_PLAYER = "player";
	const std::string TAG_PARTICLE_SYSTEM = "particle_system";
	const std::string TAG_HEALING_PACK = "health";

	const std::string NAME_PLAYER = "player";

	const std::string FONT_REGULAR = "Aleo-Regular.otf";
	const std::string FONT_ITALIC = "Aleo-Italic.otf";
	const std::string FONT_MONOSPACE = "monofonto.ttf";

	const std::string PATH_TO_RESOURCES = "res/";
	const std::string PATH_TO_SPRITES = "sprites/";
	const std::string PATH_TO_FONTS = "fonts/";
	const std::string PATH_TO_SOUNDS = "sounds/";
	const std::string PATH_TO_SAVE = "save.dat";

	const std::string SOUND_EXPLOSION_LONG = "explosion_long.ogg";
	const std::string SOUND_EXPLOSION_SHORT = "explosion_short.ogg";
	const std::string SOUND_PLAYER_SHOOT = "player_shoot.ogg";
	const std::string SOUND_ENEMY_SHOOT = "enemy_shoot.ogg";
	const std::string SOUND_MENU_CLICK = "menu_click.ogg";


	const sf::Vector2i WINDOW_SIZE = sf::Vector2i(1024, 768);
	const sf::Rect<int> SCENE_BOUNDS = sf::Rect<int>(0, 64, WINDOW_SIZE.x, WINDOW_SIZE.y-64*2-8);
}

#endif