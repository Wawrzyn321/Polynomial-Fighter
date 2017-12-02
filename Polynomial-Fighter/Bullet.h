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
	float bonusDamageMultiplier;

	void initGraphics();

	void checkCollisions();

	void checkBounds();

public:
	sf::IntRect bounds;
	Bullet(const std::string& name, const sf::Vector2f& position, float radius, float damage, float bonusDamageMultiplier = 1);

	void setTarget(const std::shared_ptr<Entity> recipient, float velocity);

	void setTarget(const std::shared_ptr<Entity> recipient, const sf::Vector2f& normalizedDirection, float velocity);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f &position) override;

	void update(Time::TimeData timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif