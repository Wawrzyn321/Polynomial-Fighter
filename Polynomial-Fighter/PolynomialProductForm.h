#ifndef POLYNOMIAL_FIGHTER_POLYNOMIAL_H
#define POLYNOMIAL_FIGHTER_POLYNOMIAL_H

#include <vector>
#include <string>
#include <set>
#include "PolynomialFactor.h"

class PolynomialMultipler;

class PolynomialProductForm
{
    friend class PolynomialMultipler;
private:
    std::vector<PolynomialFactor> factors;
public:
	size_t getDeg() const;
    void addFactor(int x, int constant);
    void addFactor(const PolynomialFactor &factor);
    void removeFactorsByRoot(int root);
    void removeAllFactors();
    bool isRoot(int root) const;
    std::set<int> getRoots() const;
};


#endif //POLYNOMIAL_FIGHTER_POLYNOMIAL_H
