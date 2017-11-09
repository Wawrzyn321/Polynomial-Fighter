#include "PolynomialGenerator.h"

PolynomialProductForm PolynomialGenerator::generatePolynomial(unsigned int deg, unsigned int valuesRange)
{
    PolynomialProductForm polynomial;

    for (int i = 0; i < deg; i++)
    {
        PolynomialFactor factor;
        do
        {
            int x;
            do
            {
                x = RandomGenerator::getInt(-static_cast<int>(valuesRange), valuesRange);
            }
            while (x == 0);
            factor.setX(x);
            factor.setConstant(RandomGenerator::getInt(-static_cast<int>(valuesRange), valuesRange));
        }
        while (!factor.isRootInteger());
        std::cout << "Wylosowany factor: x = " << factor.getX() << " const = " << factor.getConstant() << " root = " << factor.getRoot() << std::endl;
        polynomial.addFactor(factor);
    }

    return polynomial;
}
