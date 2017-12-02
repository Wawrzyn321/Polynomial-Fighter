#ifndef PLAYER_CANNON_H
#define PLAYER_CANNON_H
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <queue>

struct DesignatedTarget
{
	unsigned recipientID;
	int root;
};


class Player;
class PlayerCannon
{
	enum CannonState
	{
		IDLE,
		WAITING_FOR_AIM,
		SHOOTING,
	};


	std::queue<DesignatedTarget> targets;

	int numberOfRounds;
    sf::Vector2f origin;
	CannonState state;
	DesignatedTarget currentTarget;
	Player *playerReference;
public:
	PlayerCannon(const sf::Vector2f &origin, Player *playerReference);

	void appendTargets(const std::vector<DesignatedTarget> &targets);

	void shoot(float angle);

	void update(float deltaTime);
};


#endif
