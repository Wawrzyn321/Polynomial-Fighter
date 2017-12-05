#include "PolynomialProductForm.h"
#include <algorithm>

size_t PolynomialProductForm::getDeg() const
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
	auto list = std::remove_if(factors.begin(), factors.end(), [root](const PolynomialFactor & i)
	{
		return i.getRoot() == root;
	});
	factors.erase(list, factors.end());
}

void PolynomialProductForm::addFactor(int x, int constant)
{
    factors.emplace_back(x, constant);
}

void PolynomialProductForm::addFactor(const PolynomialFactor &factor)
{
    factors.emplace_back(factor.getX(), factor.getConstant());
}

std::set<int> PolynomialProductForm::getRoots() const
{
    std::set<int> roots;

    for (auto &i : factors)
    {
        roots.insert(i.getRoot());
    }

    return roots;
}