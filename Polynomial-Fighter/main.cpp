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
	SoundManager::instance()->isOn = false;

	hideConsole();

	auto em = EntityManager::instance();
	auto t = Time::Timer::instance();

	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(GameData::WINDOW_SIZE.x),
                                          static_cast<unsigned int>(GameData::WINDOW_SIZE.y)), "pf");
    window.setFramerateLimit(120);

	GameplayManager gameplayManager = GameplayManager(&window);

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
			gameplayManager.feed(event);
		}

		auto deltaTime = t->getTimeData();

		gameplayManager.update(deltaTime);

		em->update(deltaTime);
		em->removeMarked();
		em->addNewEntitites();

		window.clear();
		em->draw(window);
		gameplayManager.draw(window);

		window.display();
	}
	return 0;
}
