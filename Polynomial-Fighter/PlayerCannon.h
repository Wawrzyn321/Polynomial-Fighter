#ifndef PLAYER_CANNON_H
#define PLAYER_CANNON_H
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "MunitionContainer.h"
#include <memory>
#include "Entity.h"

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
class PlayerCannon : public sf::Drawable
{
	enum class CannonState
	{
		IDLE,
		WAITING_FOR_AIM,
		WAITING_FOR_RELOAD,
	};

	std::vector<DesignatedTarget> targets;

    sf::Vector2f origin;
	CannonState state;
	DesignatedTarget currentTarget;
	Player *playerReference;

	std::shared_ptr<MunitionContainer> munitionGUI;

	float reloadAccumulator;
	float reloadTime;

	void updateState();

	void getNextTarget();

	void shoot();

	void addAfterAppendText(int targetsAdded) const;
public:
	PlayerCannon(Player *playerReference);
	void appendTargets(const std::vector<int>& values, const std::vector<std::shared_ptr<Entity>> &enemies);

	void onRotationFinished(float angle);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(float deltaTime);

	~PlayerCannon();
private:
	const float defaultReloadTime = 400.0f;
};


#endif
