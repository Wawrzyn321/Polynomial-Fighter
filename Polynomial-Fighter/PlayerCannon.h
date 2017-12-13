#ifndef PLAYER_CANNON_H
#define PLAYER_CANNON_H
#include <vector>
#include <memory>
#include "PlayerCannonGraphics.h"
#include "MunitionContainer.h"
#include "Entity.h"
#include "DesignatedTarget.h"

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
	std::shared_ptr<PlayerCannonGraphics> graphics;

	float reloadAccumulator;
	float reloadTime;

	void updateState();

	void getNextTarget();

	void shoot();

	void addAfterAppendText(int targetsAdded) const;

	void initGraphics();

public:
	PlayerCannon(){}
	PlayerCannon(Player *playerReference, const sf::Vector2f &origin);

	void appendTargets(const std::vector<int>& values, const std::vector<std::shared_ptr<Entity>> &enemies);

	void onRotationFinished(float angle);

	void setPosition(const sf::Vector2f& position) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(float deltaTime);

	~PlayerCannon();
private:
	const float defaultReloadTime = 400.0f;
};


#endif
