#ifndef BULLET_BASE_H
#define BULLET_BASE_H
#include "Entity.h"

class BulletBase : public Entity
{
protected:
	sf::Vector2f velocity;
	long recipientID{};
	float radius{};
	
	void checkCollisions();

	void checkBounds();

	virtual void hitTarget(const std::shared_ptr<Entity>& target) = 0;

public:
	sf::IntRect bounds;
};



#endif