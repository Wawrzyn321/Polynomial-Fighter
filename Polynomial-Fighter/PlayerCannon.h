#ifndef PLAYER_CANNON_H
#define PLAYER_CANNON_H
#include <vector>
#include <SFML/System/Vector2.hpp>

class Player;

class PlayerCannon
{
	std::vector<int> targets;

	int numberOfRounds;
	float originX;
	float originY;
public:
	PlayerCannon(Player *player);

	void setTargets(const std::vector<int>& targets);

	void shoot(float angle);
};


#endif
