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


		tGUI.handleEvent(event);

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
		{
			animator->ring.majorValues.center.y += 20.0f;
			animator->ring.state = GUIRing::State::TO_MAJOR;
			Debug::PrintFormatted("% %\n", animator->ring.majorValues.center.y, animator->ring.majorValues.radius);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
		{
			animator->ring.majorValues.center.y -= 20.0f;
			animator->ring.state = GUIRing::State::TO_MAJOR;
			Debug::PrintFormatted("% %\n", animator->ring.majorValues.center.y, animator->ring.majorValues.radius);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
		{
			animator->ring.majorValues.radius = animator->ring.shape.getRadius() + 20.0f;
			animator->ring.state = GUIRing::State::TO_MAJOR;
			Debug::PrintFormatted("% %\n", animator->ring.majorValues.center.y, animator->ring.majorValues.radius);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J)
		{
			animator->ring.majorValues.radius = animator->ring.shape.getRadius() - 20.0f;
			animator->ring.state = GUIRing::State::TO_MAJOR;
			Debug::PrintFormatted("% %\n", animator->ring.majorValues.center.y, animator->ring.majorValues.radius);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
		{
			animator->ring.state = GUIRing::State::TO_MAJOR;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
		{
			animator->ring.state = GUIRing::State::TO_MINOR;
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
	}
}

void MainMenu::update()
{
	auto deltaTime = Time::Timer::instance()->getTimeData();

	animator->update(deltaTime);
}

void MainMenu::draw()
{
	window->clear();

	tGUI.draw();
	animator->draw(*window);

	window->display();
}

MainMenu::MainMenu(sf::RenderWindow* window)
{
	this->window = window;

	Time::Timer::instance()->reset();

	tGUI.setWindow(*window);
	animator = new GUIAnimator(&tGUI);

	isRunning = true;
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

MainMenu::~MainMenu()
{
	delete animator;
}
