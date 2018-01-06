#include <cmath>
#include "PolynomialFactor.h"
#include "Debug.h"

PolynomialFactor::PolynomialFactor(int x, int constant) : x(x), constant(constant) {}

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

int PolynomialFactor::getRoot() const
{
	return x == 0 ? 0 : -constant / x;
}

bool PolynomialFactor::isInteger(double n) const
{
    return (std::trunc(n) == n);
}

bool PolynomialFactor::isRootInteger() const
{
    return isInteger(static_cast<double> (-constant) / static_cast<double> (x));
}