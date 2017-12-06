#ifndef ENEMY_CANNON_H
#define ENEMY_CANNON_H

class Enemy;
class EnemyCannon
{
	float accumulator;
	float reloadTime;

	Enemy *enemyReference;
	float bonusBulletDamage;

	void shoot();

public:
	EnemyCannon(Enemy *enemyReference, int polynomialDegree);

	void update(float deltaTime);

	void resetAccumulator();

private:
	const float baseReloadTime = 2000.0f;
	const float baseBulletDamage = 200.0f;//1.2f;
	const float bulletRadius = 2.0f;
	const float bulletSpeed = 0.5f;
};

#endif