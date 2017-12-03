#ifndef SIGNED_BULLET_H
#define SIGNED_BULLET_H
#include "Bullet.h"
#include "Utility.h"

class SignedBullet : public Bullet
{
	int load;
	sf::Text caption;

	void initGraphics() override;
protected:
	void hitTarget(const std::shared_ptr<Entity>& target) override;
public:
	SignedBullet(const std::string& name, const sf::Vector2f& position, float radius, float damage, int load, float bonusDamageMultiplier = 1);

	void setPosition(const sf::Vector2f &position) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif