#include "EquationProvider.h"

EquationProvider::EquationProvider() { }

Equation EquationProvider::getEquation(std::vector<int> coefficients, int multiplier)
{
	return Equation { coefficients, (unsigned)coefficients.size(), multiplier };
}

//todo krzywa rozk�adu �eby potem wsp�czynniki nie by�y za du�e
std::vector<int> EquationProvider::getRandomSolutions(unsigned number)
{
	std::vector<int> v;
	for (unsigned i = 0; i < number; i++) {
		v.push_back(rand() % 3 + 1);
	}
	return v;
}
