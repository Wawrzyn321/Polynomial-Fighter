#include "PauseController.h"
#include "AssetManager.h"
#include "SoundManager.h"

void PauseController::initGraphics()
{
	font = AssetManager::instance()->getDefaultFont();

	pauseText = sf::Text("          Paused\n\nPress 'Esc' to exit.", *font, fontSize);
	centerTextOrigin(pauseText);
	pauseText.setPosition(GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.49f);
	pauseText.setFillColor(currentColor.toColor());
}

void PauseController::checkThreshold(float difference)
{
	if (difference < colorThreshold)
	{
		if (mode == Mode::UNPAUSING)
		{
			currentColor = sf::Color::Transparent;
			mode = Mode::NONE;
			Time::Timer::instance()->setTimeScale(1.0f);
			OnUnpausingFinished();
		}
		else
		{
			mode = Mode::PAUSED;
			Time::Timer::instance()->setTimeScale(0.0f);
			OnPausingFinished();
		}
	}
}

void PauseController::handleColorChange(const sf::Color& color, float deltaTime)
{
	currentColor = currentColor.lerpTo(color, deltaTime * lerpingSpeed, true);
	pauseText.setFillColor(currentColor.toColor());

	float colorDifference = currentColor.calculateMaxDifference(color, true);
	if (mode == Mode::UNPAUSING)
	{
		colorDifference = 1 - colorDifference;
	}

	Time::Timer::instance()->setTimeScale(colorDifference);
	checkThreshold(colorDifference);
}

PauseController::PauseController()
{
	mode = Mode::NONE;
	currentColor = sf::Color::Transparent;

	initGraphics();
}

void PauseController::switchPause()
{
	if (isPaused())
	{
		mode = Mode::UNPAUSING;
	}
	else 
	{
		mode = Mode::PAUSING;
		SoundManager::instance()->playSound(Assets::SOUND_PAUSE);
	}
}

void PauseController::forceSwitchTo(bool pause)
{
	if (pause)
	{
		mode = Mode::PAUSING;
	}
	else
	{
		mode = Mode::UNPAUSING;
	}
}

bool PauseController::isPaused() const
{
	return mode == Mode::PAUSING || mode == Mode::PAUSED;
}

void PauseController::feed(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		sf::Keyboard::Key key = event.key.code;
		if (key == sf::Keyboard::P)
		{
			switchPause();
		}
		else if (key == sf::Keyboard::Escape)
		{
			if (isPaused())
			{
				OnExitRequested();
			}
			else
			{
				switchPause();
			}
		}
	}
	if (event.type == sf::Event::LostFocus) {
		forceSwitchTo(true);
	}
	else if (event.type == sf::Event::GainedFocus) {
		forceSwitchTo(false);
	}
	if (event.type == sf::Event::MouseWheelMoved)
	{
		Time::Timer *t = Time::Timer::instance();
		t->setTimeScale(t->getTimeScale() + event.mouseWheel.delta*0.1f);
		if (t->getTimeScale() == 0)
		{
			forceSwitchTo(false);
		}
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			Time::Timer::instance()->setTimeScale(1);
		}
	}
}

void PauseController::update(const Time::TimeData& timeData)
{
	float deltaTime = timeData.getScaledDeltaTimeInMili();

	switch (mode) { 
	case Mode::PAUSING:
		handleColorChange(Colors::textColor, deltaTime);
		break;
	case Mode::PAUSED:
	{
		auto elapsedTime = timeData.elapsedTime.asSeconds();
		float sinValue = sinf(elapsedTime * 2.0f);
		currentColor = { currentColor.x, currentColor.y, currentColor.z, 0.75f + sinValue * 0.25f };
		pauseText.setFillColor(currentColor.toColor());
	}
	break;
	case Mode::UNPAUSING:
		handleColorChange(sf::Color::Transparent, deltaTime);
		break;
	}
}

void PauseController::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pauseText, states);
}
