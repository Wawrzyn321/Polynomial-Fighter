#ifndef ENEMY_POLYNOMIAL_ADAPTER_h
#define ENEMY_POLYNOMIAL_ADAPTER_h
#include "PolynomialProductForm.h"
#include <memory>

class Enemy;
class EnemyPolynomialAdapter
{
	unsigned originalDegree;
	int commonDivisor = 1;

	PolynomialProductForm ppf;
	std::shared_ptr<Enemy> enemyReference{};

public:
	EnemyPolynomialAdapter(const std::shared_ptr<Enemy> &enemyReference, PolynomialProductForm pff);

	bool canBeDamagedBy(int value) const;

	bool canBeReducedBy(int divisor) const;

	void reduceCoefficientsBy(int divisor);

	int decreasePolynomialByRoot(int root);

	unsigned getOriginalDegree() const;

	unsigned getDeg() const;

};

#endif