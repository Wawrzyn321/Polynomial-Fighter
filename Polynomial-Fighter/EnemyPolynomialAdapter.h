#ifndef ENEMY_POLYNOMIAL_ADAPTER_h
#define ENEMY_POLYNOMIAL_ADAPTER_h
#include "PolynomialProductForm.h"

class Enemy;
class EnemyPolynomialAdapter
{
	Enemy *enemyReference{};
	unsigned originalDegree;
	int commonDivisor = 1;
	PolynomialProductForm ppf;
public:
	EnemyPolynomialAdapter(Enemy *enemyReference, PolynomialProductForm pff);

	bool canBeDamagedBy(int value) const;

	bool canBeReducedBy(int divisor) const;

	void reduceCoefficientsBy(int divisor);

	int decreasePolynomialByRoot(int root);

	unsigned getOriginalDegree() const;

	unsigned getDeg() const;

};

#endif