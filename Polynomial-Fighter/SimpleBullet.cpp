#include "SimpleBullet.h"
#include "EntityManager.h"
#include "IDamageable.h"
#include "GameData.h"
#include "Debug.h"
#include <cassert>
#include "ParticleMaster.h"

void SimpleBullet::initGraphics()
{
	shape = sf::CircleShape(radius, (size_t) pointCount);
	shape.setOrigin(radius, radius);
}

void SimpleBullet::hitTarget(const std::shared_ptr<Entity>& target)
{
	auto d = std::dynamic_pointer_cast<IDamageable>(target);
	assert(d);
	d->receiveDamage(damage, vectorNormalize(velocity), bonusDamageMultiplier);
	trail->setEnabled(false);
	trail->setToDelete(true);
}

SimpleBullet::SimpleBullet(const sf::Vector2f& position, float radius, float damage, float bonusDamageMultiplier)
{
	this->radius = radius;
	this->damage = damage;
	this->bonusDamageMultiplier = bonusDamageMultiplier;
	name = "Bullet";
	collisionRadius = radius;
	tag = GameData::TAG_BULLET;
	bounds = GameData::DEFAULT_BOUNDS;
	recipientID = -1;

	initGraphics();
	SimpleBullet::setPosition(position);
}

void SimpleBullet::setTarget(const std::shared_ptr<Entity> &recipient, float speed)
{
	if(!recipient)
	{
		Debug::PrintErrorFormatted("Bullet::setTarget: recipient is null!\n");
		return;
	}
	this->recipientID = recipient->getId();

	sf::Vector2f currentTargetPosition = recipient->getPosition();
	velocity = vectorNormalize(currentTargetPosition - getPosition()) * speed;
	trail = ParticleMaster::addEnemyTrail(*dynamic_cast<Entity*>(this));
}

sf::Vector2f SimpleBullet::getPosition() const
{
	return shape.getPosition();
}

void SimpleBullet::setPosition(const sf::Vector2f &position)
{
	shape.setPosition(position);
}

void SimpleBullet::update(const Time::TimeData &timeData)
{
	setPosition(getPosition() + velocity * timeData.getScaledDeltaTimeInMili());

	checkCollisions();
	checkBounds();
}

void SimpleBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

