#include <iostream>
#include "InputField.h"
#include "EquationProvider.h"
#include "RandomGenerator.h"
#include "Timer.h"
#include "InputFieldParser.h"
#include "PolynomialProductForm.h"
#include "PolynomialGenerator.h"
#include "PolynomialMultipler.h"

using namespace std;

void showVector(vector<int> v) {
	for (const auto &i : v) { //todo ładne
		cout << i << " ";
	}
	cout << endl;
}

PolynomialProductForm pf;

void fun(const string &str)
{
	InputFieldParser p = InputFieldParser();
	auto v = p.parse(str);

	system("cls");
	for (int root : v)
	{
		if(pf.isRoot(root))
		{
			cout << root << " to pierwiasnetek" << endl;
			pf.removeFactorsByRoot(root);
		}
	}
	if(pf.getRoots().size() == 0)
	{
		cout << "to już wszystko, nowy wielomian: ";
		pf = PolynomialGenerator::generatePolynomial(3);
	}

	cout << PolynomialMultipler::generalForm(pf).toString() << endl;

}

void inputFieldTest()
{
	cout << endl;
	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_SIZE.x, GameData::WINDOW_SIZE.y), "IF");

	Time::Timer *t = Time::Timer::instance();

	InputField f = InputField({ 200, 100 }, { 200, 50 });
	
	f.OnTextSubmitted.add(fun);
	f.interactable = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
				f.interactable = !f.interactable;
			}

			f.feed(event);
		}
		Time::TimeData timeData = t->getTimeData();

		f.update(timeData);

		window.clear(sf::Color(127,127,127));
		window.draw(f);
		window.display();
	}
}

int main()
{
	srand(time(NULL));
//#ifdef  _WIN32
//	//hide console
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

	pf = PolynomialGenerator::generatePolynomial(5);

	cout << PolynomialMultipler::generalForm(pf).toString() << endl;

	InputFieldParser::runTests();
	inputFieldTest();

	system("pause");
	return 0;
}