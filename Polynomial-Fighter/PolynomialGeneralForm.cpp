#include <iostream>
#include "PolynomialGeneralForm.h"

int PolynomialGeneralForm::getDeg() const
{
    return static_cast<int> (coefficients.size()) - 1;
}

int PolynomialGeneralForm::getCoefficient(unsigned int deg) const
{
    if ((static_cast<int> (coefficients.size()) - 1) >= static_cast<int> (deg))
    {
        return coefficients[deg];
    }

    return 0;
}

std::string PolynomialGeneralForm::toString() const
{
    return stringRepresentation;
}

void PolynomialGeneralForm::setCoefficient(unsigned int deg, int value)
{
    if ((static_cast<int> (coefficients.size()) - 1) >= static_cast<int> (deg))
    {
        coefficients[deg] = value;
    }
    else
    {
        coefficients.resize(deg + 1, 0);
        coefficients[deg] = value;
    }

    generateString();
}

void PolynomialGeneralForm::generateString()
{
	stringRepresentation.clear();
    auto iterator = coefficients.end();

    for (int i = 0; i < coefficients.size(); i++)
    {
        iterator--; //TODO: V803 https://www.viva64.com/en/w/V803 Decreased performance. In case 'iterator' is iterator it's more effective to use prefix form of decrement. Replace iterator-- with --iterator.
        if (*iterator == 0) continue;

        int deg = coefficients.size() - 1 - i;
        std::string temp;
        int coefficient = *iterator;

        if (i > 0 && coefficient > 0)
        {
            temp += " +";
        }
        else if (i > 0)
        {
            temp += " ";
        }

        if (deg > 0)
        {
            if (std::abs(coefficient) > 1)
            {
                temp += std::to_string(coefficient);
            }
            else if (coefficient < 0)
            {
                temp += "-";
            }
        }
        else
        {
            temp += std::to_string(coefficient);
        }

        if (deg > 0)
        {
            temp += "x";

            if (deg > 1)
            {
                temp += "^";
                temp += std::to_string(deg);
            }
        }

        stringRepresentation += temp;
    }
}

bool PolynomialGeneralForm::divideCoefficients(int divider)
{
    for (const auto &i : coefficients)
    {
        if (i % divider != 0)
        {
            return false;
        }
    }

    for (auto &i : coefficients)
    {
        i /= divider;
    }

    generateString();

    return true;
}
