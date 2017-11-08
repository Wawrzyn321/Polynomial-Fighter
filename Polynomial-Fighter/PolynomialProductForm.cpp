#include "PolynomialProductForm.h"

unsigned int PolynomialProductForm::getDeg() const
{
    return factors.size();
}

bool PolynomialProductForm::isRoot(int root) const
{
    for (auto &i : factors)
    {
        if (i.getRoot() == root)
        {
            return true;
        }
    }

    return false;
}

void PolynomialProductForm::removeAllFactors()
{
    factors.clear();
}

void PolynomialProductForm::removeFactorsByRoot(int root)
{
    for (int i = 0; i < factors.size(); i++)
    {
        if (factors[i].getRoot() == root)
        {
            factors.erase(factors.begin() + i);
        }
    }
}

void PolynomialProductForm::addFactor(int x, int constant)
{
    factors.emplace_back(x, constant);
}