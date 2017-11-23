#include "Bullet.h"
#include "EntityManager.h"
#include "IDamageable.h"
#include "ITransformable.h"
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
	auto target = EntityManager::instance()->findEntityByName(recipientName);
	Entity* e = target.lock().get();
	if (checkCollision((ITransformable*)e))
	{
		((IDamageable*)e)->receiveDamage(damage, vectorNormalize(velocity), bonusDamage);
		markedForDeletion = true;
	}
	//po auto ostrzeniu
	if (checkCollision(static_cast<ITransformable*>(e)))
	{
		reinterpret_cast<IDamageable*>(e)->receiveDamage(damage, vectorNormalize(velocity), bonusDamage);
		markedForDeletion = true;
	}
}

void Bullet::checkBounds()
{
	sf::Vector2f v = getPosition();
	if (v.x < -radius || v.y < -radius ||
		v.x > GameData::WINDOW_SIZE.x + radius
		|| v.y > GameData::WINDOW_SIZE.y + radius)
	{
		Debug::PrintFormatted("ha\n");
		/*Entity *e = (Entity*)this;
		std::shared_ptr<Entity> sp = std::shared_ptr<Entity>(e);
		std::weak_ptr<Entity> p = std::weak_ptr<Entity>(sp);
		EntityManager::instance()->deleteEntity(p);*/
		markedForDeletion = true;
	}
}

Bullet::Bullet(const std::string& name, const sf::Vector2f& position, float radius)
{
	this->name = name;
	this->radius = radius;
	collisionRadius = radius;
	tag = GameData::TAG_BULLET;
	bounds = sf::IntRect({0,0}, GameData::WINDOW_SIZE);

	initGraphics();

	setPosition(position);
}

void Bullet::setTarget(const sf::Vector2f& targetPosition, const std::string& recipient, float velocity, float damage,
                       float bonusDamage)
{
	this->velocity = vectorNormalize(targetPosition - getPosition()) * velocity;
	this->recipientName = recipient;
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
