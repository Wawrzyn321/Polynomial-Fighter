#include "EnemyCannon.h"
#include "Enemy.h"
#include "SimpleBullet.h"
#include "EntityManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "AssetManager.h"

void EnemyCannon::shoot()
{
	auto player = EntityManager::instance()->findEntityOfType<Player>();

	if (player && player->getAlive()) {
		auto b = std::make_shared<SimpleBullet>(enemyReference->getPosition(), bulletRadius, baseBulletDamage, bonusBulletDamage);
		b->setTarget(player, bulletSpeed);
		EntityManager::instance()->addEntity(b);

		std::string s = Assets::SOUND_ENEMY_SHOOT;
		s[Assets::SOUND_ENEMY_SHOOT_REPLACE] = '0' + RandomGenerator::getInt(1, 3);
		SoundManager::instance()->playSound(s, enemyReference->getPosition());
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