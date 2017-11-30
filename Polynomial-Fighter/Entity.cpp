#include "Entity.h"
#include "Debug.h"

bool Entity::checkCollision(Entity &other)
{
    if (!collisionsEnabled) return false;

    if(other.getCollisionRadius() == 0)
    {
        Debug::PrintFormatted("<other> Entity has collision radius = 0!\n");
    }

    if(collisionRadius == 0)
    {
        Debug::PrintFormatted("Entity has collision radius = 0!\n");
    }

    return squaredDistance(getPosition(), other.getPosition()) <=
        (collisionRadius + other.getCollisionRadius()) * (collisionRadius + other.getCollisionRadius());
}

float Entity::getCollisionRadius() const
{
    return collisionRadius;
}
sf::Vector2f Entity::getPosition() const
{
    return position;
}
