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
	auto target = EntityManager::instance()->findEntityById(recipientID);
	Entity* e = target.lock().get();
	if (checkCollision(static_cast<ITransformable*>(e)))
	{
		Debug::PrintFormatted("przed wywolaniem receive: {%} -> ", e->name);
		auto d = reinterpret_cast<IDamageable*>(e);
		Debug::PrintFormatted("tutaj IDam: <%>", d);
		d->receiveDamage(damage, vectorNormalize(velocity), bonusDamage);
		Debug::PrintFormatted("i po wywolaniu {%}\n", e->name);
		toDelete = true;
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
		toDelete = true;
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

void Bullet::setTarget(const std::weak_ptr<Entity> recipient, float velocity, float damage,
                       float bonusDamage)
{
	sf::Vector2f currentTargetPosition = ((ITransformable*)(recipient.lock().get()))->getPosition();
	this->velocity = vectorNormalize(currentTargetPosition - getPosition()) * velocity;
	this->recipientID = recipient.lock().get()->getId();
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
