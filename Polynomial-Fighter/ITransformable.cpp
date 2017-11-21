#include "ITransformable.h"
#include "Utility.h"

bool ITransformable::checkCollision(ITransformable* other)
{
	if(other->getCollisionRadius() == 0)
	{
		Debug::PrintFormatted("<other> Entity has collision radius = 0!\n");
	}
	if(collisionRadius == 0)
	{
		Debug::PrintFormatted("Entity has collision radius = 0!\n");
	}
	if (!collisionsEnabled) return false;
	return squaredDistance(getPosition(), other->getPosition()) <=
		(collisionRadius + other->getCollisionRadius()) * (collisionRadius + other->getCollisionRadius());
}

float ITransformable::getCollisionRadius()
{
	return collisionRadius;
}
