#ifndef POLYNOMIAL_FIGHTER_POLYNOMIALGENERATOR_H
#define POLYNOMIAL_FIGHTER_POLYNOMIALGENERATOR_H

#include "RandomGenerator.h"
#include "PolynomialProductForm.h"
#include <iostream>

class PolynomialGenerator
{
public:
    static PolynomialProductForm generatePolynomial(unsigned int deg, unsigned int valuesRange = 2);
};


#endif //POLYNOMIAL_FIGHTER_POLYNOMIALGENERATOR_H
