#include "MainMenu.h"
#include "Timer.h"


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

		if (event.type == sf::Event::KeyPressed && state == State::SPLASH)
		{
			animator->setMenu(true);
			state = State::MENU;
		}
		else if (state == State::HIGHSCORES)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
			{
				animator->moveHighscoresUp();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				animator->moveHighscoresDown();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				animator->setMenu(false);
				animator->setHighscoresVisible(false);
				state = State::MENU;
			}
		}
		else if (state == State::HOW_TO)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
			{
				animator->moveHowToUp();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				animator->moveHowToUp();
			}
		}
		else if (state == State::MENU) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && state == State::MENU)
			{
				animator->setSplash();
				state = State::SPLASH;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				animator->rotateRingRight();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
			{
				animator->rotateRingLeft();
			}
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)) {
				animator->setHowToVisible(false);
				animator->setHighscoresVisible(false);
				switch (animator->getRingOption()) {
				case GUIRingOptions::Option::PLAY:
					Debug::PrintFormatted("PLAY\n");
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
					stopWatch->OnTime.add(std::bind(&MainMenu::finish, this));
					break;
				case GUIRingOptions::Option::SOUND:
					SoundManager::instance()->isOn = !SoundManager::instance()->isOn;
					animator->setSound(SoundManager::instance()->isOn);
					break;
				}
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

void MainMenu::finish()
{
	isRunning = false;
	stopWatch->OnTime.clear();
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
	window->clear();

	animator->draw(*window);

	window->display();
}

MainMenu::~MainMenu()
{
	delete animator;
	delete stopWatch;
}
