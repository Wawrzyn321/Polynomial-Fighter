#ifndef EQUATION_PROVIDER_H
#define EQUATION_PROVIDER_H

#include "Debug.h"
#include <vector>
#include <string>


struct Equation {

	std::vector<int> solutions;
	unsigned maxSolutions;
	int multiplier;

	std::string toString() {
		//todo no kurde brzydko
		size_t size = solutions.size();
		int n = multiplier;

		if (size == 1) { 
			int a = solutions[0];
			return std::to_string(n) + "x -" + std::to_string(n*a);
		}

		if (size == 2) { 
			int a = solutions[0];
			int b = solutions[1];
			return std::to_string(n) + "x^2 " + std::to_string((-a - b) * n) + "x +" + std::to_string(n * a * b);
		}
		if (size == 3) {
			int a = solutions[0];
			int b = solutions[1];
			int c = solutions[2];
			return std::to_string(n) + "x^3 -" +
				std::to_string((a + b + c)*n) + " x^2 +" +
				std::to_string(n*(a * b + b * c + a * c)) + "x -" +
				std::to_string((n)*a * b * c);
		}
		if (size == 4) {
			int a = solutions[0];
			int b = solutions[1];
			int c = solutions[2];
			int d = solutions[3];
			return std::to_string(n) + "x^4 " +
				std::to_string(n*(-a - b - c - d)) + "x^3 +" +
				std::to_string(n*(a*b+a*c+a*d+c*b+c*d+d*b))+ "x^2 " +
				std::to_string(-n*(a*c*d+b*c*d+a*b*c+a*b*d))+ "x +" +
				std::to_string((n)*a * b * c * d);
		}
		return "nie";
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
