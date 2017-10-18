#include "EquationProvider.h"

Equation EquationProvider::getEquation(std::vector<int> coefficients, int multiplier) const
{
	return Equation { coefficients, (unsigned)coefficients.size(), multiplier };
}

//todo krzywa rozkładu żeby potem współczynniki nie były za duże
std::vector<int> EquationProvider::getRandomSolutions(unsigned number) const
{
	std::vector<int> v;
	for (unsigned i = 0; i < number; i++)
	{
		int val = rand() % 3 + 1;
		val *= (rand() % 2) * 2 - 1;
		v.push_back(val);
	}
	return v;
}
