#ifndef SIGNED_BULLET_H
#define SIGNED_BULLET_H
#include "Utility.h"
#include "BulletBase.h"

class SignedBullet : public BulletBase {
	int load{};
	sf::Text caption;
	sf::Text symbol;
	std::shared_ptr<sf::Font> font;

	void initGraphics();

	void hitTarget(const std::shared_ptr<Entity>& target) override;
public:
	sf::IntRect bounds;
	SignedBullet(const sf::Vector2f& position, float radius, int load);

	void setTarget(const std::shared_ptr<Entity>& recipient, float speed);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f &position) override;

	void update(const Time::TimeData &timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	const float rotationSpeed = 0.7f;
	const float defaultCollisionRadius = 10.0f;
};

#endif