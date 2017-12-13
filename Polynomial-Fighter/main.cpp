#include "Timer.h"
#include "EntityManager.h"
#include "Player.h"
#include "AdvancedParticleSystem.h"
#include "GameplayManager.h"
#include "InputField.h"

using namespace std;

void hideConsole()
{
	//#ifdef  _WIN32
	//	//hide console
	//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	//#endif
}

int main()
{
	hideConsole();

	auto em = EntityManager::instance();
	auto t = Time::Timer::instance();

	GameplayManager gameplayManager = GameplayManager();

	InputField inputField = InputField(
	{ GameData::WINDOW_SIZE.x *0.67f, GameData::WINDOW_SIZE.y*0.89f },
	{ GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f }
	);
	inputField.OnTextSubmitted.add(std::bind(&GameplayManager::TextSubmitted, &gameplayManager, std::placeholders::_1));

	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_SIZE.x, GameData::WINDOW_SIZE.y), "pf");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
			if (event.type == sf::Event::LostFocus) {
				t->setTimeScale(0);
			}

			if (event.type == sf::Event::GainedFocus) {
				t->setTimeScale(1);
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				t->setTimeScale(t->getTimeScale() + event.mouseWheel.delta*0.1f);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					t->setTimeScale(1);
				}
			}
			inputField.feed(event);
		}

		auto deltaTime = t->getTimeData();

		gameplayManager.update(deltaTime);
		inputField.update(deltaTime);

		em->update(deltaTime);
		em->removeMarked();
		em->addNewEntitites();

		window.clear();
		em->draw(window);
		window.draw(inputField);
		window.display();
	}
	return 0;
}
