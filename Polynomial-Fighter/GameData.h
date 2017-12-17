#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <SFML/Graphics.hpp>
#include "PlayerCannon.h"
#include "Enemy.h"

namespace GameData {

	const std::string TAG_ENEMY = "enemy";
	const std::string TAG_BULLET = "bullet";
	const std::string TAG_SIGNED_BULLET = "signed_bullet";
	const std::string TAG_PLAYER = "player";
	const std::string TAG_PARTICLE_SYSTEM = "particle_system";
	const std::string TAG_HEALING_PACK = "health";

	const std::string NAME_PLAYER = "player";
	const std::string NAME_PARTICLE_SYSTEM = "Particle System";

	const std::string FONT_REGULAR = "Aleo-Regular.otf";
	const std::string FONT_ITALIC = "Aleo-Italic.otf";
	const std::string FONT_MONOSPACE = "monofonto.ttf";

	const std::string PATH_TO_RESOURCES = "res/";
	const std::string PATH_TO_IMAGES = "img/";
	const std::string PATH_TO_FONTS = "fonts/";
	const std::string PATH_TO_SOUNDS = "sounds/";
	const std::string PATH_TO_SAVE = "save.dat";

	const std::string SPRITESHEET = "spritesheet.png";

	const std::string SOUND_MENU_CLICK = ""; //@TODO

	const std::string SOUND_PLAYER_SHOOT = "player_shoot.ogg";
	const std::string SOUND_ENEMY_SHOOT = "enemy_shoot.ogg";
	const sf::Vector2i WINDOW_SIZE = sf::Vector2i(1024, 768);
	const sf::IntRect DEFAULT_BOUNDS = sf::IntRect({ 0,0 }, WINDOW_SIZE);;

	const unsigned MAX_POLYNOMINAL_DEGREE = 7;
	const unsigned MAX_POLYNOMINAL_VALUE = 5;
}

#endif