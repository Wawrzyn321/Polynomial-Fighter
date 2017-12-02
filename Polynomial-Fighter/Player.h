#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "Entity.h"
#include "IDamageable.h"
#include "Delegate.h"
#include "PlayerHealthGUI.h"
#include "PlayerCannon.h"

class Player : public Entity, public IDamageable
{
	sf::RectangleShape shape;
	float health;
	float maxHealth;

	std::unique_ptr<PlayerHealthGUI> healthGUI;
	std::unique_ptr<PlayerCannon> cannon;

	float targetRotation;
	bool rotationEventInvoked = true;

	void initGraphics();

	void updateRotation(float deltaTime);

public:
	Delegate<int> DeathEvent;
	Delegate<float> FinishedRotatingEvent;

	Player(const sf::Vector2f &position);

	void setTargetPosition(const sf::Vector2f& position);

	void appendTargets(const std::vector<DesignatedTarget>& targets);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f &position) override;

	void onDestroy() override;

	void update(Time::TimeData timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void receiveDamage(float damage, float bonusDamageMultiplier) override;

	void receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier) override;
};

#endif
