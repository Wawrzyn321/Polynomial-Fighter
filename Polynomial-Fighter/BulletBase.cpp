#include "BulletBase.h"
#include "EntityManager.h"

void BulletBase::checkCollisions()
{
	auto target = EntityManager::instance()->findEntityById(recipientID);
	if (checkCollision(target))
	{
		hitTarget(target);
		setToDelete(true);
	}
}

void BulletBase::checkBounds()
{
	sf::Vector2f pos = getPosition();
	bool xExceeded = pos.x < -radius || pos.x > GameData::WINDOW_SIZE.x + radius;
	bool yExceeded = pos.y < -radius || pos.y > GameData::WINDOW_SIZE.y + radius;
	if (xExceeded || yExceeded)
	{
		setToDelete(true);
	}
}