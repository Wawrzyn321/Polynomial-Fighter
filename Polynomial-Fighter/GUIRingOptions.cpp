#include "GUIRingOptions.h"
#include "FleetingText.h"
#include "Utility.h"
#include "Colors.h"
#include "AssetManager.h"

GUIRingOptions::GUIRingOptions(const sf::Vector2f &center)
{
	currentOption = 0;
	commonRotation = 0;
	currentPosition = 0;

	font = AssetManager::instance()->getDefaultFont();

	button_play = new sf::Text("Play", *font, fontSize);
	button_howto = new sf::Text("How to play", *font, fontSize);
	button_highscores = new sf::Text("Highscores", *font, fontSize);
	button_exit = new sf::Text("Exit", *font, fontSize);
	button_sound = new sf::Text("Sound: On", *font, fontSize);
	button_authors = new sf::Text("Authors", *font, fontSize);

	buttons = {
		button_play, button_howto,
		button_highscores, button_exit,
		button_authors, button_sound };

	for (unsigned i = 0; i < buttons.size(); i++)
	{
		centerTextOrigin(*buttons[i]);
		buttons[i]->setOrigin(buttons[i]->getOrigin().x, buttons[i]->getOrigin().y + radius);
		buttons[i]->setPosition({ center.x, 0 });
		buttons[i]->setRotation(i * 360.0f / buttons.size());
	}
}

void GUIRingOptions::handleDistanceMoving(float deltaTime)
{
	float y;
	if (isVisible)
	{
		y = GameData::WINDOW_SIZE.y*1.71875f;
	}
	else if (isZoomed)
	{
		y = GameData::WINDOW_SIZE.y*1.25f;
	}
	else
	{
		y = GameData::WINDOW_SIZE.y*0.8f;
	}

	for (sf::Text* b : buttons)
	{
		b->setPosition(lerp(b->getPosition(), { b->getPosition().x, y }, rotationSpeed*deltaTime));
	}
}

void GUIRingOptions::handleRotating(float deltaTime)
{
	float targetRotation = -currentOption*360.0f / buttons.size();
	float deltaAngle = minAngleDifference(commonRotation, lerpAngle(commonRotation, targetRotation, deltaTime*rotationSpeed));
	commonRotation += deltaAngle;

	if (abs(deltaAngle) > rotationThreshold)
	{
		for (sf::Text* b : buttons)
		{
			b->rotate(deltaAngle);
		}
	}
	else
	{
		commonRotation = targetRotation;
		for (unsigned i = 0; i < buttons.size(); i++)
		{
			buttons[i]->setRotation(targetRotation + i * 360.0f / buttons.size());
		}
		isUpdatngRotation = false;

	}
}

void GUIRingOptions::handleColoring(float deltaTime)
{
	auto lerping = [](auto b, auto color, float deltaTime) { b->setFillColor(lerp(b->getFillColor(), color, deltaTime)); };

	for (unsigned i = 0; i < buttons.size(); i++)
	{
		sf::Color color;

		if (isExiting || isTransitioningToGame) { color = sf::Color::Transparent; }
		else if (i == currentOption) { color = Colors::FIFTH; }
		else { color = Colors::THIRD; }

		lerping(buttons[i], color , deltaTime * 0.003f);
	}
}

void GUIRingOptions::update(float deltaTime)
{
	handleDistanceMoving(deltaTime);

	if (isUpdatngRotation)
	{
		handleRotating(deltaTime);
	}
	if (isVisible)
	{
		handleColoring(deltaTime);
	}
	
}

void GUIRingOptions::setExiting()
{
	isExiting = true;
}

void GUIRingOptions::switchLeft()
{
	currentOption = (currentOption + 1) % buttons.size();
	isUpdatngRotation = true;
}

void GUIRingOptions::switchRight()
{
	currentOption--;
	if (currentOption<0)
	{
		currentOption = int(buttons.size()) - 1;
	}
	isUpdatngRotation = true;
}

void GUIRingOptions::setVisible(bool isVisible, bool resetCurrentOption)
{
	this->isVisible = isVisible;
	if (isVisible)
	{
		if (resetCurrentOption) {
			currentOption = 0;
		}
		isUpdatngRotation = true;
	}
}

void GUIRingOptions::setSoundOn(bool isOn) const
{
	button_sound->setString("Sound: O" + std::string(isOn ?  "n" : "ff"));
}

GUIRingOptions::Option GUIRingOptions::getCurrentOption() const
{
	return static_cast<Option>(currentOption);
}

void GUIRingOptions::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (sf::Text* b : buttons)
	{
		target.draw(*b, states);
	}
}

GUIRingOptions::~GUIRingOptions()
{
	for (sf::Text* b : buttons)
	{
		delete b;
	}
}
