#include "TextArrows.h"
#include "Utility.h"
#include "AssetManager.h"
#include "Colors.h"

TextArrows::TextArrows(unsigned fontSize)
{
	font = AssetManager::instance()->getDefaultFont();

	fontSize = unsigned(fontSize * 1.5f);

	leftArrow = sf::Text("<", *font, fontSize);
	leftArrow.setFillColor(Colors::textLitColor);
	leftArrow.rotate(-5);

	rightArrow = sf::Text(">", *font, fontSize);
	rightArrow.setFillColor(Colors::textLitColor);
	leftArrow.rotate(5);

	xLeft = -GameData::WINDOW_SIZE.x *0.2f;
	xRight = GameData::WINDOW_SIZE.x *1.2f;
	rightArrow.setPosition(xRight, yPosition);
}

void TextArrows::updateBounds(const sf::Text *text)
{
	float xCenter = GameData::WINDOW_CENTER.x;

	sf::FloatRect textRect = text->getLocalBounds();
	float widthHalved = textRect.left + textRect.width / 2.0f;
	xLeft = xCenter - widthHalved - GameData::WINDOW_SIZE.x*0.07f;
	xRight = xCenter + widthHalved + GameData::WINDOW_SIZE.x*0.01f;
}

void TextArrows::updateBounds(float xLeft, float xRight)
{
	this->xLeft = xLeft;
	this->xRight = xRight;
}

void TextArrows::setOuttaGame()
{
	this->xLeft = -GameData::WINDOW_SIZE.x * 0.2f;
	this->xRight = GameData::WINDOW_SIZE.x * 1.2f;
}

void TextArrows::update(const Time::TimeData& timeData)
{
	float lerpingSpeed = 0.01f;
	float lerpAmound = timeData.getScaledDeltaTimeInMili() * lerpingSpeed;
	leftArrow.setPosition(lerp(leftArrow.getPosition(), { xLeft, yPosition }, lerpAmound));
	rightArrow.setPosition(lerp(rightArrow.getPosition(), { xRight, yPosition }, lerpAmound));
}

void TextArrows::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftArrow, states);
	target.draw(rightArrow, states);
}
