#ifndef ITRANSFORMABLE
#define ITRANSFORMABLE

#include <SFML\Graphics.hpp>
#include "Utility.h"

class ITransformable {
	//friend bool BulletBase::isOutsideBounds(void);
protected:
	sf::Sprite baseSprite;
    float collisionRadius;
    virtual bool checkCollision(ITransformable *other) {
		if (!collisionsEnabled) return false;
        return squaredDistance(getPosition(), other->getPosition()) <=
            (collisionRadius + other->getCollisionRadius())*(collisionRadius + other->getCollisionRadius());
    }
public:
	bool collisionsEnabled = true;

	virtual sf::Vector2f getPosition() = NULL;
	virtual void setPosition(sf::Vector2f position) = NULL;
    virtual float getCollisionRadius() {
        return collisionRadius;
    }
};


#endif