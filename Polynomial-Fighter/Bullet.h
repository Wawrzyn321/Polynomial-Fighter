#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bullet : public Entity {
	sf::CircleShape shape;
	sf::Vector2f velocity;
	long recipientID;
	float radius;
	float damage;
	float bonusDamage;

	void initGraphics();

	void checkCollisions();

	void checkBounds();

public:
	sf::IntRect bounds;
	Bullet(const std::string& name, const sf::Vector2f& position, float radius);

	void setTarget(const Entity &recipient, float velocity, float damage, float bonusDamage = 1);

	sf::Vector2f getPosition();

	void setPosition(sf::Vector2f position) override;

	void update(Time::TimeData timeData) override;;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif