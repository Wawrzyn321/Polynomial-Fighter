#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <SFML/Graphics.hpp>

namespace GameData {

	const std::string TAG_ENEMY = "enemy";
	const std::string TAG_BULLET = "bullet";
	const std::string TAG_SIGNED_BULLET = "signed_bullet";
	const std::string TAG_PLAYER = "player";
	const std::string TAG_PARTICLE_SYSTEM = "particle_system";
	const std::string TAG_HEALING_PACK = "health";

	const std::string NAME_PLAYER = "player";
	const std::string NAME_PARTICLE_SYSTEM = "Particle System";

	const sf::Vector2i WINDOW_SIZE = sf::Vector2i(1024, 768);
	const sf::Vector2f WINDOW_CENTER = {WINDOW_SIZE.x*0.5f, WINDOW_SIZE.y*0.5f};
	const sf::IntRect DEFAULT_BOUNDS = sf::IntRect({ 0,0 }, WINDOW_SIZE);;

	const float fillingSpeed = 0.05f;
	const float unscalingSpeed = 0.01f;
	const float scaleMultiplier = 1.3f;
	const float minScalingThreshold = 0.01f;

	const unsigned MAX_POLYNOMINAL_DEGREE = 7;
	const unsigned MAX_POLYNOMINAL_VALUE = 5;
}

#endif