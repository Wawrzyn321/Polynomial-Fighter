#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "Entity.h"
#include "IDamageable.h"
#include "Delegate.h"
#include "PlayerHealthGUI.h"

class Player: public Entity, public IDamageable
{
	sf::RectangleShape shape;
	std::unique_ptr<PlayerHealthGUI> healthGUI;
	float health;
	float maxHealth;

	void initGraphics();
public:
	Delegate<int> DeathEvent;

	Player(const sf::Vector2f &position);

	sf::Vector2f getPosition() override;

	void setPosition(sf::Vector2f position) override;

	void onDestroy() override;

	void update(Time::TimeData timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void receiveDamage(float damage, float bonusDamageMultiplier) override;

	void receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier) override;
	
};

#endif
