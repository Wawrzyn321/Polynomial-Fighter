#include "Bullet.h"
#include "EntityManager.h"
#include "IDamageable.h"
#include "GameData.h"
#include "Debug.h"
#include <cassert>

void Bullet::initGraphics()
{
	const int pointCount = 16;

	shape = sf::CircleShape(radius, pointCount);
	shape.setOrigin(radius, radius);
	//todo set color
}

void Bullet::hitTarget(const std::shared_ptr<Entity>& target)
{
	auto d = std::dynamic_pointer_cast<IDamageable>(target);
	assert(d);
	d->receiveDamage(damage, vectorNormalize(velocity), bonusDamageMultiplier);
}

void Bullet::checkCollisions()
{
	auto target = EntityManager::instance()->findEntityById(recipientID);
	//TODO
	//checkCollision, receive damage
	//musza brac jako argument referencje do shared_ptr, zwykle wskazniki to zlo i nie uzywamy ich
	//£ADNIE TO ZROBI£EM.
	if (checkCollision(target))
	{
		hitTarget(target);
		toDelete = true;
	}
}

void Bullet::checkBounds()
{
	sf::Vector2f pos = getPosition();
	bool xExceeded = pos.x < -radius || pos.x > GameData::WINDOW_SIZE.x + radius;
	bool yExceeded = pos.y < -radius || pos.y > GameData::WINDOW_SIZE.y + radius;
	if (xExceeded || yExceeded)
	{
		toDelete = true;
	}
}

Bullet::Bullet(const std::string& name, const sf::Vector2f& position, float radius, float damage, float bonusDamageMultiplier)
{
	this->name = name;
	this->radius = radius;
	this->damage = damage;
	this->bonusDamageMultiplier = bonusDamageMultiplier;
	collisionRadius = radius;
	tag = GameData::TAG_BULLET;
	bounds = GameData::DEFAULT_BOUNDS;
	recipientID = -1;

	Bullet::initGraphics();
	Bullet::setPosition(position);
}

void Bullet::setTarget(const std::shared_ptr<Entity> &recipient, float velocity)
{
	if(!recipient)
	{
		Debug::PrintErrorFormatted("Bullet::setTarget: recipient is null!\n");
		return;
	}
	sf::Vector2f currentTargetPosition = recipient->getPosition();
	this->velocity = vectorNormalize(currentTargetPosition - getPosition()) * velocity;
	this->recipientID = recipient->getId();
}

void Bullet::setTarget(const std::shared_ptr<Entity> &recipient, const sf::Vector2f& normalizedDirection, float velocity)
{
	if (!recipient)
	{
		Debug::PrintErrorFormatted("Bullet::setTarget: recipient is null!\n");
		return;
	}
	this->velocity = normalizedDirection * velocity;
	this->recipientID = recipient->getId();
}

sf::Vector2f Bullet::getPosition() const
{
	//todo add const
	return shape.getPosition();
}

void Bullet::setPosition(const sf::Vector2f &position)
{
	//todo add const
	shape.setPosition(position);
}

void Bullet::update(const Time::TimeData &timeData)
{
	setPosition(getPosition() + velocity * timeData.getScaledDeltaTimeInMili());

	checkCollisions();
	checkBounds();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}
