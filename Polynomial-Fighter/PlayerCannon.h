#ifndef PLAYER_CANNON_H
#define PLAYER_CANNON_H
#include <vector>
#include <SFML/System/Vector2.hpp>

class Player;

class PlayerCannon
{
	std::vector<int> targets;

	int numberOfRounds;
    sf::Vector2f origin;
public:
	PlayerCannon(sf::Vector2f origin);

	void setTargets(const std::vector<int> &targets);

	void shoot(float angle);

	void update(float deltaTime);
};


#endif
