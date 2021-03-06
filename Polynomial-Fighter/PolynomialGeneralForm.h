#ifndef POLYNOMIAL_FIGHTER_POLYNOMIALGENERALFORM_H
#define POLYNOMIAL_FIGHTER_POLYNOMIALGENERALFORM_H

#include <string>
#include <vector>

class PolynomialGeneralForm
{
private:
    std::vector<int> coefficients; //[0] to 0 stopien, [1] to 1
    std::string stringRepresentation;
    void generateString();
public:
    int getDeg() const;
    void setCoefficient(unsigned int deg, int value);
    int getCoefficient(unsigned int deg) const;
    std::string toString() const;
	bool canDivideCoefficients(int divider) const; // mozna wyrzucic sprawdzanie i typ z divideCoefficients?
    bool divideCoefficients(int divider); //podzieli tylko i wylacznie, gdy wszystkie sie calkowicie dziela
};


#endif //POLYNOMIAL_FIGHTER_POLYNOMIALGENERALFORM_H
