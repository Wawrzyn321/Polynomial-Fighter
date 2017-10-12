#include "PoolManager.h"
#include "ParticleSystem.h"

PoolManager *PoolManager::sInstance = NULL;

PoolManager * PoolManager::instance()
{
	if (sInstance == NULL) {
		sInstance = new PoolManager();
		sInstance->entityManager = EntityManager::instance();
	}
	return sInstance;
}

#pragma region Getting objects

//void PoolManager::drawPlayerBullet(sf::Vector2f position, sf::Vector2f direction) {
//	for (int i = 0; i < entityManager->entities.size(); i++) {
//		Entity *e = entityManager->entities[i];
//		if (e->tag == GameData::TAG_PLAYER_BULLET) {
//			if (e->getEnabled() == false) {
//				((PlayerBullet*)e)->refresh(position, direction);
//				e->setEnabled(true);
//				return;
//			}
//		}
//	}
//	PlayerBullet *playerBullet = new PlayerBullet(position, direction);
//	entityManager->addEntity((Entity*)playerBullet);
//}

#pragma endregion
