#include "FlashingText.h"
#include "Utility.h"
#include "AssetManager.h"
#include "Colors.h"

void FlashingText::flash(float elapsedTime)
{
	float sinValue = sinf(elapsedTime * flashingSpeed);
	currentColor = { currentColor.x, currentColor.y, currentColor.z, 0.75f + sinValue * 0.25f };
	text.setFillColor(currentColor.toColor());
}

void FlashingText::handleMovement(float deltaTime)
{
	sf::Vector2f dest = state == State::TO_POS_1 ? pos1 : pos2;
	sf::Vector2f pos = lerp(text.getPosition(), dest, deltaTime * lerpSpeed);
	text.setPosition(pos);

	if (abs(dest.x - pos.x) < vector2Threshold && abs(dest.y - pos.y) < vector2Threshold)
	{
		text.setPosition(dest);
		state = State::IDLE;
	}
}

FlashingText::FlashingText(const std::string& caption, const sf::Vector2f &position, unsigned fontSize)
{
	font = AssetManager::instance()->getDefaultFont();
	currentColor = Colors::SECOND;

	text = sf::Text(caption, *font, fontSize);
	centerTextOrigin(text);
	text.setPosition(position);
	text.setFillColor(currentColor.toColor());

	state = State::IDLE;
	canFlash = false;
}

void FlashingText::setStateValues(const sf::Vector2f &pos1, const sf::Vector2f &pos2)
{
	this->pos1 = pos1;
	this->pos2 = pos2;
}

void FlashingText::update(const Time::TimeData &timeData)
{
	if (state != State::IDLE) {
		handleMovement(timeData.getScaledDeltaTimeInMili());
	}

	if (canFlash) {
		flash(timeData.elapsedTime.asSeconds());
	}
}

void FlashingText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}
