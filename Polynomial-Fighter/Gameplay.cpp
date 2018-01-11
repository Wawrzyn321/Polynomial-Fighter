#include "Gameplay.h"
#include "Timer.h"
#include "GameplayManager.h"
#include "EntityManager.h"

void Gameplay::handleEvents()
{
	auto t = Time::Timer::instance();

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
			return;
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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
		{
			isRunning = false;
		}
		gameplayManager->feed(event);
	}
}

void Gameplay::update() const
{
	auto deltaTime = Time::Timer::instance()->getTimeData();

	gameplayManager->update(deltaTime);

	em->update(deltaTime);
	em->removeMarked();
	em->addNewEntitites();
}

void Gameplay::draw() const
{
	window->clear(Colors::backgroundColor);
	em->draw(*window);

	gameplayManager->draw(*window);

	window->display();
}

Gameplay::Gameplay(sf::RenderWindow* window)
{
	this->window = window;

	Time::Timer::instance()->reset();

	em = EntityManager::instance();
	gameplayManager = new GameplayManager(window);

	isRunning = true;
}

void Gameplay::mainLoop()
{
	while (isRunning && window->isOpen())
	{
		handleEvents();

		update();

		draw();
	}
}

Gameplay::~Gameplay()
{
	delete gameplayManager;
}
