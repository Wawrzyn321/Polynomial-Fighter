#ifndef ITRANSFORMABLE
#define ITRANSFORMABLE

#include <SFML/Graphics.hpp>

class ITransformable {
protected:
    float collisionRadius = 0;
	virtual bool checkCollision(ITransformable* other);
public:
	virtual ~ITransformable() = default;
	bool collisionsEnabled = true;

	virtual sf::Vector2f getPosition() = 0;
	virtual void setPosition(sf::Vector2f position) = 0;
	virtual float getCollisionRadius();
};


#endif