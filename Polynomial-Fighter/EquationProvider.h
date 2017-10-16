#ifndef EQUATION_PROVIDER_H
#define EQUATION_PROVIDER_H

#include "Debug.h"
#include <vector>
#include <string>


struct Equation {

	std::vector<int> solutions;
	unsigned maxSolutions;
	int multiplier;

	/*
	//todo
	1: n(	x																					  -a	)
	2: n(	x^2		+x(-1)(a+b)																	 +ab	)
	3: n(	x^3		+x^2(a+b+c)			+x(ab+bc+ac)											-abc	)
	4: n(	x^4		+x^3(-1)(a+b+c+d)	+x^2(ab+ac+cd+bc+bd+cd)		+x(-1)(abc+acd+abd+bcd)	   +abcd	)
	*/

	std::string toString() {
		//todo no kurde brzydko
		size_t size = solutions.size();
		int n = multiplier;

		int sum, product;//OBSERWACJE

		if (size == 1) { 
			int a = solutions[0];
			product = a;
			return std::to_string(n) + "x -" + std::to_string(n*product);
		}

		if (size == 2) { 
			int a = solutions[0];
			int b = solutions[1];
			sum = a + b;
			product = a*b;
			return std::to_string(n) + "x^2 " + std::to_string(-sum * n) + "x +" + std::to_string(n * product);
		}
		if (size == 3) {
			int a = solutions[0];
			int b = solutions[1];
			int c = solutions[2];
			sum = a + b + c;
			product = a * b * c;
			return std::to_string(n) + "x^3 -" +
				std::to_string(sum*n) + " x^2 +" +
				std::to_string(n*(a * b + b * c + a * c)) + "x -" +
				std::to_string(n*product);
		}

	}

	bool isSolution(int val) {
		for (auto &solution : solutions) {
			if (val == solution) {
				return true;
			}
		}
		return false;
	}
};

class EquationProvider {

public:
	EquationProvider();

	Equation getEquation(std::vector<int> solutions, int multiplier = 1);

	std::vector<int> getRandomSolutions(unsigned number);

};

#endif EQUATION_PROVIDER_H