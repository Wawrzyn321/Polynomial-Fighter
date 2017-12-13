#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "BulletBase.h"

class SimpleBullet : public BulletBase {
	sf::CircleShape shape;
	float damage;
	float bonusDamageMultiplier;

	void initGraphics();

	void hitTarget(const std::shared_ptr<Entity>& target) override;
public:
	SimpleBullet(const sf::Vector2f& position, float radius, float damage, float bonusDamageMultiplier = 1);

	void setTarget(const std::shared_ptr<Entity>& recipient, float speed);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f &position) override;

	void update(const Time::TimeData &timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	const int pointCount = 16;
};

#endif