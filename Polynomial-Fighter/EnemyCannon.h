#ifndef ENEMY_CANNON_H
#define ENEMY_CANNON_H
#include <memory>

class Enemy;
class EnemyCannon
{
	float accumulator{};
	float reloadTime{};

	std::shared_ptr<Enemy> enemyReference{};

	void shoot() const;

public:
	EnemyCannon(const std::shared_ptr<Enemy> &enemyReference);

	void update(float deltaTime);

	void resetAccumulator();

	~EnemyCannon() = default;

private:
	const float baseReloadTime = 2000.0f;
	const float baseBulletDamage = 1.2f;
	const float bulletRadius = 2.0f;
	const float bulletSpeed = 0.5f;
};

#endif