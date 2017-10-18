#include <iostream>
#include <time.h>
#include "EquationProvider.h"
#include "RandomGenerator.h"

using namespace std;

void showVector(vector<int> v) {
	for (const auto &i : v) { //todo ładne
		cout << i << " ";
	}
	cout << endl;
}

int main()
{

//#ifdef  _WIN32
//	//hide console
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

//	EquationProvider ep = EquationProvider();
//
//	const int stopnie = 4; //działa dla 4 stopnia, dalej...
//	const int probki = 8;
//	const int multi = 3;
//
//	for (unsigned i = 1; i <= stopnie; i++) {
//
//		for (unsigned j = 0; j < probki; j++) {
//
//			vector<int> sols = ep.getRandomSolutions(i);
//
//			int multiplier = rand() % multi + 1;
//
//			cout << "mult: "<< multiplier <<endl<<"tutaj rozw: ";
//
//			showVector(sols);
//
//			Equation e = ep.getEquation(sols, multiplier);
//
//			cout << e.toString() << endl;
//
//		}
//
//	}

	cout << RandomGenerator::getDouble(1.0, 3.4);

	system("pause");
	return 0;
}