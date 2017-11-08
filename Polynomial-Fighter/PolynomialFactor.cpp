#include "PolynomialFactor.h"

int PolynomialFactor::getX() const
{
    return x;
}

void PolynomialFactor::setX(int x)
{
    PolynomialFactor::x = x;
}

int PolynomialFactor::getConstant() const
{
    return constant;
}

void PolynomialFactor::setConstant(int constant)
{
    PolynomialFactor::constant = constant;
}

PolynomialFactor::PolynomialFactor(int x, int constant) : x(x), constant(constant) {}

int PolynomialFactor::getRoot() const
{
    return -constant / x;
}
