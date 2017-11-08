#ifndef POLYNOMIAL_FIGHTER_POLYNOMIALFACTOR_H
#define POLYNOMIAL_FIGHTER_POLYNOMIALFACTOR_H


class PolynomialFactor
{
private:
    int x;
    int constant;

public:
    PolynomialFactor(int x = 0, int constant = 0);
    int getX() const;
    void setX(int x);
    int getConstant() const;
    void setConstant(int constant);
    int getRoot() const;
};


#endif //POLYNOMIAL_FIGHTER_POLYNOMIALFACTOR_H