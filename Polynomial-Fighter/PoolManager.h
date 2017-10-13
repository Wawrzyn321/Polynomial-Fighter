#ifndef POOL_MANAGER_H
#define POOL_MANAGER_H

#include "Utility.h"
#include "EntityManager.h"
//#include "EnemyBullet.h"

class PoolManager {
	
private:
	PoolManager() {}
	static PoolManager*sInstance;

	EntityManager *entityManager = nullptr;
public:
	static PoolManager *instance();
	
	void drawPlayerBullet(sf::Vector2f position, sf::Vector2f direction);

	void drawEnemyBullet(sf::Vector2f position, float bonusDamage);

	void drawOnHitParticles(sf::Vector2f position, sf::Vector2f direction);

	void drawPlayerDestroyedParticles(sf::Vector2f position);

	void drawEnemyDestroyedParticles(sf::Vector2f position);
};


#endif