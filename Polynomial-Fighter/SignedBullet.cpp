#include "SignedBullet.h"
#include "GameData.h"
#include "Enemy.h"
#include <cassert>

void SignedBullet::initGraphics()
{
	const unsigned fontSize = 16;

	Bullet::initGraphics();

	std::string captionText = "x = " + std::to_string(load);
	caption = sf::Text(captionText, *AssetManager::instance()->getDefaultFont(), fontSize);
	centerTextOrigin(caption);
}

void SignedBullet::hitTarget(const std::shared_ptr<Entity>& target)
{
	Bullet::hitTarget(target);
	auto enemy = std::dynamic_pointer_cast<Enemy>(target);
	assert(enemy);
	enemy->decreasePolynomial(load);
}

SignedBullet::SignedBullet(const sf::Vector2f & position, float radius, float damage, int load, float bonusDamageMultiplier) :
	Bullet(position, radius, damage, bonusDamageMultiplier)
{
	this->load = load;

	name = "SignedBullet";
	tag = GameData::TAG_DESIGNATED_BULLET;
}

void SignedBullet::setPosition(const sf::Vector2f& position)
{
	const float captionYShift = -30;

	Bullet::setPosition(position);
	caption.setPosition(position + sf::Vector2f(0, captionYShift));
}


void SignedBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Bullet::draw(target, states);
	target.draw(caption, states);
}
