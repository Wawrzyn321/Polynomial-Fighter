#include "MainMenu.h"
#include "Timer.h"
#include "SoundManager.h"

void MainMenu::handleMenuEvents(const sf::Event::KeyEvent& key)
{
	switch (key.code)
	{
	case sf::Keyboard::Escape:
		animator->setSplash();
		state = State::SPLASH;
		break;
	case sf::Keyboard::Space:
	case sf::Keyboard::Return:
		animator->setHowToVisible(false);
		animator->setHighscoresVisibles(false);
		animator->setAuthorsVisible(false);
		switch (animator->getRingOption()) {
		case GUIRingOptions::Option::PLAY:
		{
			animator->setToGame();
			state = State::TO_GAME;
			stopWatch->reset(900, true);
			stopWatch->OnTime.add(std::bind(&MainMenu::onGame, this));
			SoundManager::instance()->playSound(Assets::SOUND_GAME_LOAD);
		}
		break;
		case GUIRingOptions::Option::HOW_TO:
			animator->setEmptyCenter();
			animator->setHowToVisible(true);
			state = State::HOW_TO;
			SoundManager::instance()->playSound(Assets::SOUND_CLICK);
			break;
		case GUIRingOptions::Option::HIGHSCORES:
			animator->setEmptyCenter();
			animator->setHighscoresVisibles(true);
			state = State::HIGHSCORES;
			SoundManager::instance()->playSound(Assets::SOUND_CLICK);
			break;
		case GUIRingOptions::Option::AUTHORS:
			animator->setEmptyCenter();
			animator->setAuthorsVisible(true);
			state = State::AUHTORS;
			SoundManager::instance()->playSound(Assets::SOUND_CLICK);
			break;
		case GUIRingOptions::Option::EXIT:
			animator->setExiting();
			state = State::EXITING;
			stopWatch->reset(800, true);
			stopWatch->OnTime.add(std::bind(&MainMenu::exitGame, this));
			SoundManager::instance()->playSound(Assets::SOUND_EXIT);
			break;
		case GUIRingOptions::Option::SOUND:
			SoundManager::instance()->isOn = !SoundManager::instance()->isOn;
			animator->setSound(SoundManager::instance()->isOn);
			if(SoundManager::instance()->isOn)
			{
				SoundManager::instance()->playSound(Assets::SOUND_SOUND_ON);
			}
			break;
		}
	}
}

void MainMenu::handleSplashEvents(const sf::Event::KeyEvent& key){
	if (!key.alt && !key.shift) {
		animator->setMenu(true, false);
		state = State::MENU;
		SoundManager::instance()->playSound(Assets::SOUND_MENU_LOAD);
	}
}

void MainMenu::handleHighScoreKeys(const sf::Event::KeyEvent& key)
{
	switch (key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		animator->moveHighscoresUp();
		SoundManager::instance()->playSound(Assets::SOUND_ROLLING_LIST_MOVE);
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		animator->moveHighscoresDown();
		SoundManager::instance()->playSound(Assets::SOUND_ROLLING_LIST_MOVE);
		break;
	case sf::Keyboard::Escape:
		animator->setMenu(false, false);
		animator->setHighscoresVisibles(false);
		state = State::MENU;
		SoundManager::instance()->playSound(Assets::SOUND_MENU_BACK);
		break;
	}
}

void MainMenu::handleHowToKeys(const sf::Event::KeyEvent& key)
{
	switch (key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		animator->moveHowToUp();
		SoundManager::instance()->playSound(Assets::SOUND_ROLLING_LIST_MOVE);
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		animator->moveHowToDown();
		SoundManager::instance()->playSound(Assets::SOUND_ROLLING_LIST_MOVE);
		break;
	case sf::Keyboard::Escape:
		animator->setMenu(false, false);
		animator->setHowToVisible(false);
		state = State::MENU;
		SoundManager::instance()->playSound(Assets::SOUND_MENU_BACK);
		break;
	}
}

void MainMenu::handleAuthorsKeys(const sf::Event::KeyEvent& key)
{
	switch (key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		animator->moveAuthorsUp();
		SoundManager::instance()->playSound(Assets::SOUND_ROLLING_LIST_MOVE);
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		animator->moveAuthorsDown();
		SoundManager::instance()->playSound(Assets::SOUND_ROLLING_LIST_MOVE);
		break;
	case sf::Keyboard::Escape:
		animator->setMenu(false, false);
		animator->setAuthorsVisible(false);
		state = State::MENU;
		SoundManager::instance()->playSound(Assets::SOUND_MENU_BACK);
		break;
	}
}

void MainMenu::handleRingRotation(const sf::Event &event) const
{
	static bool lock = false;

	sf::Keyboard::Key key = event.key.code;

	if (event.type == sf::Event::KeyPressed && !lock) {
		switch (key) {
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			animator->rotateRingLeft();
			SoundManager::instance()->playSound(Assets::SOUND_CLICK, SoundManager::SoundDirection::LEFT);
			lock = true;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			animator->rotateRingRight();
			SoundManager::instance()->playSound(Assets::SOUND_CLICK, SoundManager::SoundDirection::RIGHT);
			lock = true;
			break;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (key == sf::Keyboard::A || key == sf::Keyboard::D || key == sf::Keyboard::Left || key == sf::Keyboard::Right) {
			lock = false;
		}
	}
}

void MainMenu::handleEvents()
{
	auto t = Time::Timer::instance();

	sf::Event event;
	while (window->pollEvent(event))
	{
		/*sf::Listener::setPosition(GameData::WINDOW_SIZE.x*0.5f, 0.0f, GameData::WINDOW_SIZE.y*0.5f);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right) {
				auto v = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				SoundManager::instance()->playSound(Assets::SOUND_EXPLOSION_SHORT, v);
			}
		}*/

		if (event.type == sf::Event::Closed) {
			window->close();
			return;
		}
		if (event.type == sf::Event::LostFocus) {
			t->setTimeScale(0);
		}

		if (state == State::MENU) {
			handleRingRotation(event);
		}

		if (event.type == sf::Event::KeyPressed) {
			switch (state) {
			case State::SPLASH:
				handleSplashEvents(event.key);
				break;
			case State::MENU:
				handleMenuEvents(event.key);
				break;
			case State::HIGHSCORES:
				handleHighScoreKeys(event.key);
				break;
			case State::HOW_TO:
				handleHowToKeys(event.key);
				break;
			case State::AUHTORS:
				handleAuthorsKeys(event.key);
				break;
			}
		}

		if (event.type == sf::Event::GainedFocus) {
			t->setTimeScale(1);
		}
		/*if (event.type == sf::Event::MouseWheelMoved)
		{
			t->setTimeScale(t->getTimeScale() + event.mouseWheel.delta*0.1f);
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Middle)
			{
				t->setTimeScale(1);
			}
		}*/
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

	animator->setMenu(true, false);
	state = State::MENU;
}

MainMenu::MainMenu(sf::RenderWindow* window)
{
	this->window = window;
	window->setIcon(32, 32, AssetManager::instance()->getTexture(Assets::ICON)->copyToImage().getPixelsPtr());

	Time::Timer::instance()->reset();

	stopWatch = new StopWatch();
	animator = new GUIAnimator(this);
	sf::Listener::setPosition(GameData::WINDOW_SIZE.x*0.5f, 0, GameData::WINDOW_SIZE.y*0.5f);

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
