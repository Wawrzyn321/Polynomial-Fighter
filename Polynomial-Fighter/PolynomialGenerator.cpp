#include "PolynomialGenerator.h"

PolynomialProductForm PolynomialGenerator::generatePolynomial(unsigned int deg, unsigned int valuesRange)
{
	PolynomialProductForm polynomial;


	{
		PolynomialFactor factor;
		do
		{
			int x = 1;
			do
			{
				x = RandomGenerator::getInt(-static_cast<int>(valuesRange), valuesRange);
			} while (x == 0);
			factor.setX(x);
			factor.setConstant(RandomGenerator::getInt(-static_cast<int>(valuesRange), valuesRange));
		} while (!factor.isRootInteger());
		std::cout << "Wylosowany factor: x = " << factor.getX() << " const = " << factor.getConstant() << " root = " << factor.getRoot() << std::endl;
		polynomial.addFactor(factor);
	}

	return polynomial;
}
