#ifndef POLYNOMIAL_FIGHTER_POLYNOMIALMULTIPLER_H
#define POLYNOMIAL_FIGHTER_POLYNOMIALMULTIPLER_H

#include "PolynomialGeneralForm.h"
#include "PolynomialProductForm.h"

class PolynomialMultipler
{
private:
    static PolynomialGeneralForm factorToGeneral(const PolynomialFactor &factor);
    static PolynomialGeneralForm multiplyGenerals(const PolynomialGeneralForm &general1, const PolynomialGeneralForm &general2);
public:
    static PolynomialGeneralForm generalForm(const PolynomialProductForm &productForm);
};


#endif //POLYNOMIAL_FIGHTER_POLYNOMIALMULTIPLER_H