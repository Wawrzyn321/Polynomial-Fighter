#include "EnemyCannon.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "Player.h"

void EnemyCannon::shoot()
{
	auto player = EntityManager::instance()->findEntityOfType<Player>();

	if (player) {
		auto b = std::make_shared<Bullet>(enemyReference->getPosition(), bulletRadius, baseBulletDamage, bonusBulletDamage);
		b->setTarget(player, bulletSpeed);
		EntityManager::instance()->addEntity(b);
	}
}

EnemyCannon::EnemyCannon(Enemy *enemyReference, int polynomialDegree)
{
	this->enemyReference = enemyReference;

	accumulator = 0;
	reloadTime = baseReloadTime - polynomialDegree * 100;
	bonusBulletDamage = 1.0f + polynomialDegree*0.1f;
}

void EnemyCannon::update(float deltaTime)
{
	accumulator += deltaTime;
	if (accumulator > reloadTime)
	{
		shoot();
		accumulator -= reloadTime;
	}
}

void EnemyCannon::resetAccumulator()
{
	accumulator = 0;
}