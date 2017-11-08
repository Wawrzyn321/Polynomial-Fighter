#include <stack>
#include "PolynomialMultipler.h"

PolynomialGeneralForm PolynomialMultipler::generalForm(const PolynomialProductForm &productForm)
{
    if (productForm.getDeg() == 0)
    {
        return PolynomialGeneralForm();
    }
    else if (productForm.getDeg() == 1)
    {
        PolynomialGeneralForm temp;
        temp.setCoefficient(0, productForm.factors[0].getConstant());
        temp.setCoefficient(1, productForm.factors[0].getX());
        return temp;
    }

    std::stack<PolynomialGeneralForm> partResults;
    for (int i = 0; i < productForm.getDeg() - 1; i++)
    {
        PolynomialGeneralForm g1;
        PolynomialGeneralForm g2;

        if (i == 0)
        {
            g1 = factorToGeneral(productForm.factors[i]);
            g2 = factorToGeneral(productForm.factors[i + 1]);
        }
        else
        {
            g1 = partResults.top();
            g2 = factorToGeneral(productForm.factors[i + 1]);
        }

        auto result = multiplyGenerals(g1, g2);
        partResults.push(result);
    }

    return partResults.top();

    //RECZNY TEST DLA DWOCH FACTOROW
//    auto g1 = factorToGeneral(productForm.factors[0]);
//    auto g2 = factorToGeneral(productForm.factors[1]);
//    auto result = multiplyGenerals(g1, g2);
//    return result;
}

PolynomialGeneralForm PolynomialMultipler::factorToGeneral(const PolynomialFactor &factor)
{
    PolynomialGeneralForm temp;
    temp.setCoefficient(0, factor.getConstant());
    temp.setCoefficient(1, factor.getX());
    return temp;
}

PolynomialGeneralForm
PolynomialMultipler::multiplyGenerals(const PolynomialGeneralForm &general1, const PolynomialGeneralForm &general2)
{
    PolynomialGeneralForm result;

    //algorytm wziety ze stacka, zaskakujaco prosty
    for (int i = 0; i != (general1.getDeg() + 1); i++)
        for (int j = 0; j != (general2.getDeg() + 1); j++)
            result.setCoefficient(i + j, result.getCoefficient(i + j) + general1.getCoefficient(i) * general2.getCoefficient(j));

    return result;
}

