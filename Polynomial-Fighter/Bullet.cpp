#include "Bullet.h"
#include "EntityManager.h"
#include "IDamageable.h"
#include "GameData.h"
#include "Debug.h"

void Bullet::initGraphics()
{
	const int pointCount = 16;

	shape = sf::CircleShape(radius, pointCount);
	shape.setOrigin(radius, radius);
	//todo set color
}

void Bullet::checkCollisions()
{
	auto target = EntityManager::instance()->findEntityById(recipientID);

	//TODO
	//checkCollision, receive damage
	//musza brac jako argument referencje do shared_ptr, zwykle wskazniki to zlo i nie uzywamy ich

	if (checkCollision(*target))
	{
        auto d = std::dynamic_pointer_cast<IDamageable>(target);
		d->receiveDamage(damage, vectorNormalize(velocity), bonusDamage);
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

Bullet::Bullet(const std::string& name, const sf::Vector2f& position, float radius)
{
	this->name = name;
	this->radius = radius;
	collisionRadius = radius;
	tag = GameData::TAG_BULLET;
	bounds = GameData::DEFAULT_BOUNDS;

	initGraphics();

	setPosition(position);
}

void Bullet::setTarget(const Entity &recipient, float velocity, float damage, float bonusDamage)
{
	sf::Vector2f currentTargetPosition = recipient.getPosition();
	this->velocity = vectorNormalize(currentTargetPosition - getPosition()) * velocity;
	this->recipientID = recipient.getId();
	this->damage = damage;
	this->bonusDamage = bonusDamage;
}

sf::Vector2f Bullet::getPosition()
{
	//todo add const
	return shape.getPosition();
}

void Bullet::setPosition(sf::Vector2f position)
{
	//todo add const
	shape.setPosition(position);
}

void Bullet::update(Time::TimeData timeData)
{
	setPosition(getPosition() + velocity * timeData.getScaledDeltaTimeInMili());
	checkCollisions();
	checkBounds();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}
