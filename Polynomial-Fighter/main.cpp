#include <iostream>
#include "InputField.h"
#include "EquationProvider.h"
#include "RandomGenerator.h"
#include "Timer.h"
#include "InputFieldParser.h"

using namespace std;

void showVector(vector<int> v) {
	for (const auto &i : v) { //todo ładne
		cout << i << " ";
	}
	cout << endl;
}

void fun(const string &str)
{
	InputFieldParser p = InputFieldParser();
	auto v = p.parse(str);
}

void inputFieldTest()
{
	cout << endl;
	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_SIZE.x, GameData::WINDOW_SIZE.y), "IF");

	Time::Timer *t = Time::Timer::instance();

	InputField f = InputField({ 200, 100 }, { 200, 50 });
	
	f.OnTextSubmitted.add(fun);
	f.isSelected = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
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

//#ifdef  _WIN32
//	//hide console
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

	InputFieldParser::runTests();
	inputFieldTest();

	system("pause");
	return 0;
}