#include "RollingListEntry.h"
#include "Utility.h"

RollingListEntry::RollingListEntry(sf::Text text, sf::Vector2f targetPosition)
{
	this->text = text;
	this->targetPosition = targetPosition;

	targetScale = 1;
	targetColor = Colors::WHITE;
}

void RollingListEntry::update(float deltaTime)
{
	deltaTime = clamp01(deltaTime * 0.01f);

	text.setPosition(lerp(text.getPosition(), targetPosition, deltaTime));
	float s = lerp(text.getScale().x, targetScale, deltaTime);
	text.setScale(s, s);
	text.setFillColor(lerp(text.getFillColor(), targetColor, deltaTime));
}
