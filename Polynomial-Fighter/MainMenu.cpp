#include "MainMenu.h"
#include "Timer.h"
#include "SoundManager.h"

void MainMenu::handleHighScoreKeys(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::W:
		animator->moveHighscoresUp();
		break;
	case sf::Keyboard::S:
		animator->moveHighscoresDown();
		break;
	case sf::Keyboard::Escape:
		animator->setMenu(false);
		animator->setHighscoresVisible(false);
		state = State::MENU;
		break;
	}
}

void MainMenu::handleMenuEvents(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		animator->setSplash();
		state = State::SPLASH;
		break;
	case sf::Keyboard::A:
		animator->rotateRingRight();
		break;
	case sf::Keyboard::D:
		animator->rotateRingLeft();
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::Return:
		animator->setHowToVisible(false);
		animator->setHighscoresVisible(false);
		switch (animator->getRingOption()) {
		case GUIRingOptions::Option::PLAY:
		{
			animator->setToGame();
			state = State::TO_GAME;
			stopWatch->reset(900, true);
			stopWatch->OnTime.add(std::bind(&MainMenu::onGame, this));
		}
		break;
		case GUIRingOptions::Option::HOW_TO:
			animator->setEmptyCenter();
			animator->setHowToVisible(true);
			state = State::HOW_TO;
			break;
		case GUIRingOptions::Option::HIGHSCORES:
			animator->setEmptyCenter();
			animator->setHighscoresVisible(true);
			state = State::HIGHSCORES;
			break;
		case GUIRingOptions::Option::EXIT:
			animator->setExiting();
			state = State::EXITING;
			stopWatch->reset(800, true);
			stopWatch->OnTime.add(std::bind(&MainMenu::exitGame, this));
			break;
		case GUIRingOptions::Option::SOUND:
			SoundManager::instance()->isOn = !SoundManager::instance()->isOn;
			animator->setSound(SoundManager::instance()->isOn);
			break;
		}
	}
}

void MainMenu::handleHowToKeys(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::W:
		animator->moveHowToUp();
		break;
	case sf::Keyboard::S:
		animator->moveHowToDown();
		break;
	case sf::Keyboard::Escape:
		animator->setMenu(false);
		animator->setHowToVisible(false);
		state = State::MENU;
		break;
	}
}

void MainMenu::handleEvents()
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

		if (event.type == sf::Event::KeyPressed) {
			switch (state) {
			case State::SPLASH:
				animator->setMenu(true);
				state = State::MENU;
				break;
			case State::MENU:
				handleMenuEvents(event.key.code);
				break;
			case State::HIGHSCORES:
				handleHighScoreKeys(event.key.code);
				break;
			case State::HOW_TO:
				handleHowToKeys(event.key.code);
				break;
			}
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
	}
}

void MainMenu::update() const
{
	auto deltaTime = Time::Timer::instance()->getTimeData();

	stopWatch->update(deltaTime);
	animator->update(deltaTime);
}

void MainMenu::exitGame()
{
	isRunning = false;
	stopWatch->OnTime.clear();
}

void MainMenu::onGame()
{
	stopWatch->OnTime.clear();

	Gameplay g = Gameplay(window);
	g.mainLoop();

	animator->setMenu(true);
	state = State::MENU;
}

MainMenu::MainMenu(sf::RenderWindow* window)
{
	this->window = window;

	Time::Timer::instance()->reset();

	stopWatch = new StopWatch();
	animator = new GUIAnimator(this);

	isRunning = true;
	state = State::SPLASH;
}

void MainMenu::mainLoop()
{
	while (isRunning && window->isOpen())
	{
		handleEvents();

		update();

		draw();
	}
}

void MainMenu::draw() const
{
	window->clear(Colors::screenBackgroundColor);

	animator->draw(*window);

	window->display();
}

MainMenu::~MainMenu()
{
	delete animator;
	delete stopWatch;
}
