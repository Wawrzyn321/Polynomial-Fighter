#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <iostream>
#include <SFML\Graphics.hpp>

namespace GameData {

	const sf::Vector2i WINDOW_SIZE = sf::Vector2i(1024, 768);
	const sf::Rect<int> SCENE_BOUNDS = sf::Rect<int>(0, 64, WINDOW_SIZE.x, WINDOW_SIZE.y-64*2-8);
}

#endif