#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "IDamageable.h"
#include "Debug.h"

class Enemy : public Entity, public IDamageable
{
	sf::RectangleShape shape;
	float health;
	float maxHealth;

	void initGraphics()
	{
		shape = sf::RectangleShape({ 10, 10 });
	}
public:

	Enemy(const sf::Vector2f &position)
	{
		name = "EEE";
		initGraphics();
		collisionRadius = 1;
		setPosition(position);
	}

	sf::Vector2f getPosition()
	{
		return shape.getPosition();
	}

	void setPosition(sf::Vector2f position) override
	{
		shape.setPosition(position);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(shape, states);
	}

	void receiveDamage(float damage, float bonusDamageMultiplier) override
	{
		Debug::PrintFormatted("ala");
	}

	void receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier) override
    {
		Debug::PrintFormatted("ala2");
	}


};

#endif