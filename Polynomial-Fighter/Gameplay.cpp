#include "Gameplay.h"
#include "Timer.h"
#include "GameplayManager.h"
#include "EntityManager.h"

void Gameplay::handleEvents() const
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
			return;
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
	window->clear(Colors::screenBackgroundColor);

	gameplayManager->earlyDraw(*window);

	em->draw(*window);

	gameplayManager->draw(*window);

	window->display();
}

Gameplay::Gameplay(sf::RenderWindow* window)
{
	this->window = window;

	Time::Timer::instance()->reset();

	em = EntityManager::instance();
	gameplayManager = new GameplayManager(this, window);
	gameplayManager->bindExitAction(this);

	isRunning = true;
	state = State::ON;
}

void Gameplay::mainLoop() const
{
	while (isRunning && window->isOpen())
	{
		handleEvents();

		update();

		draw();
	}

	Time::Timer::instance()->setTimeScale(1.0f);
}

Gameplay::~Gameplay()
{
	delete gameplayManager;
}
