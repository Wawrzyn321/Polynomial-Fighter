#include "Entity.h"
#include "Debug.h"

bool Entity::checkCollision(const std::shared_ptr<Entity> &other)
{
	if (!other)
	{
		Debug::PrintFormatted("Entity::checkCollision: other == null\n");
		return false;
	}

    if (!collisionsEnabled || !other->collisionsEnabled) return false;

	if(other->getId() == getId())
	{
		Debug::PrintFormatted("Entity::checkCollision: checking collision with the same body, skipping.\n");
		return false;
	}
		
    if(other->getCollisionRadius() == 0)
    {
        Debug::PrintFormatted("<other> Entity has collision radius = 0!\n");
    }

    if(collisionRadius == 0)
    {
        Debug::PrintFormatted("Entity has collision radius = 0!\n");
    }
    return squaredDistance(getPosition(), other->getPosition()) <=
        (collisionRadius + other->getCollisionRadius()) * (collisionRadius + other->getCollisionRadius());
}

float Entity::getCollisionRadius() const
{
    return collisionRadius;
}
