#include "EnemyPolynomialAdapter.h"
#include "PolynomialProductForm.h"
#include "Debug.h"
#include "PolynomialMultipler.h"
#include "Enemy.h"

EnemyPolynomialAdapter::EnemyPolynomialAdapter(Enemy * enemyReference, PolynomialProductForm ppf)
{
	this->enemyReference = enemyReference;
	this->ppf = ppf;
	originalDegree = unsigned(ppf.getDeg());
	enemyReference->setName(PolynomialMultipler::generalForm(ppf).toString());
}

bool EnemyPolynomialAdapter::canBeDamagedBy(int value) const
{
	return ppf.isRoot(value);
}

bool EnemyPolynomialAdapter::canBeReducedBy(int divisor) const
{
	return PolynomialMultipler::generalForm(ppf).canDivideCoefficients(divisor);
}

void EnemyPolynomialAdapter::reduceCoefficientsBy(int divisor)
{
	auto pgf = PolynomialMultipler::generalForm(ppf);
	bool canReduce = pgf.divideCoefficients(commonDivisor);
	if (!canReduce)
	{
		//Debug::PrintFormatted("Enemy::reduceBy: cannot reduce by %\n", divisor);
		return;
	}
	commonDivisor *= divisor;
	pgf.divideCoefficients(commonDivisor);
	enemyReference->setName(pgf.toString());
}

int EnemyPolynomialAdapter::decreasePolynomialByRoot(int root)
{
	if (!ppf.isRoot(root)) return 0;
	size_t degBefore = ppf.getDeg();
	ppf.removeFactorsByRoot(root);
	auto difference = int(degBefore - ppf.getDeg());
	if (ppf.getDeg() == 0) {
		enemyReference->invokeDeathEvent();
	}
	else {
		PolynomialGeneralForm pgf = PolynomialMultipler::generalForm(ppf);
		pgf.divideCoefficients(commonDivisor);
		enemyReference->setName(pgf.toString());
	}
	return difference;
}

unsigned EnemyPolynomialAdapter::getOriginalDegree() const
{
	return originalDegree;
}

unsigned EnemyPolynomialAdapter::getDeg() const
{
	return unsigned(ppf.getDeg());
}
