#ifndef POLYNOMIAL_FIGHTER_POLYNOMIAL_H
#define POLYNOMIAL_FIGHTER_POLYNOMIAL_H

#include <vector>
#include <string>
#include "PolynomialFactor.h"

class PolynomialMultipler;

class PolynomialProductForm
{
    friend class PolynomialMultipler;
private:
    std::vector<PolynomialFactor> factors;
public:
    unsigned int getDeg() const;
    void addFactor(int x, int constant);
    void removeFactorsByRoot(int root);
    void removeAllFactors();
    bool isRoot(int root) const;
};


#endif //POLYNOMIAL_FIGHTER_POLYNOMIAL_H