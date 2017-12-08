#ifndef PLAYER_CANNON_H
#define PLAYER_CANNON_H
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <set>

struct DesignatedTarget
{
	unsigned recipientID;
	int root;

	bool operator==(const DesignatedTarget &other) const
	{
		return other.recipientID == recipientID && other.root == root;
	}
};


class Player;
class PlayerCannon
{
	enum class CannonState
	{
		IDLE,
		WAITING_FOR_AIM,
		WAITING_FOR_RELOAD,
	};

	std::vector<DesignatedTarget> targets;

	int numberOfRounds = 9999;
    sf::Vector2f origin;
	CannonState state;
	DesignatedTarget currentTarget;
	Player *playerReference;

	float reloadAccumulator;
	float reloadTime;

	void updateState();

	void getNextTarget();

	void shoot();
public:
	PlayerCannon(Player *playerReference);

	void appendTargets(const std::vector<DesignatedTarget> &targets);

	void onRotationFinished(float angle);

	void update(float deltaTime);
private:
	const float defaultReloadTime = 400.0f;
	const int defaultNumberOfRounds = 5;

};


#endif
