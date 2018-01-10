#include "RollingList.h"
#include "Colors.h"
#include "Utility.h"

void RollingList::updateTargets()
{
	if (state == State::MOVING) {

		int indexDec = currentlyCentered - 1;
		if (indexDec < 0)
		{
			indexDec = unsigned(entries.size() - 1);
		}
		unsigned indexInc = (currentlyCentered + 1) % entries.size();

		for (unsigned i = 0; i < unsigned(indexDec); i++)
		{
			entries[i]->targetColor = sf::Color::Transparent;
			entries[i]->targetPosition = center - sf::Vector2f(0.0f, positionShift);
			entries[i]->targetScale = 0.0f;
		}
		entries[indexDec]->targetColor = lerp(sf::Color::Transparent, sf::Color::White, 0.5f);
		entries[indexDec]->targetPosition = center - sf::Vector2f(0.0f, positionShift * 0.5f);
		entries[indexDec]->targetScale = 0.707f;

		entries[currentlyCentered]->targetPosition = center;
		entries[currentlyCentered]->targetColor = Colors::textLitColor;
		entries[currentlyCentered]->targetScale = 1.0f;

		entries[indexInc]->targetColor = lerp(sf::Color::Transparent, sf::Color::White, 0.5f);
		entries[indexInc]->targetPosition = center + sf::Vector2f(0.0f, positionShift * 0.5f);
		entries[indexInc]->targetScale = 0.707f;

		for (unsigned i = indexInc + 1; i < entries.size() && i != indexDec; i++)
		{
			entries[i]->targetColor = sf::Color::Transparent;
			entries[i]->targetPosition = center + sf::Vector2f(0.0f, positionShift);
			entries[i]->targetScale = 0.0f;
		}
	}
	else if (state == State::HIDING)
	{
		for (RollingListEntry* t : entries)
		{
			t->targetPosition = center;
			t->targetScale = 0;
			t->targetColor = sf::Color::Transparent;
		}
	}
}

void RollingList::moveUp()
{
	currentlyCentered--;
	if (currentlyCentered < 0)
	{
		currentlyCentered = unsigned(entries.size()) - 1;
	}
	state = State::MOVING;
	updateTargets();
}

void RollingList::moveDown()
{
	currentlyCentered = (currentlyCentered + 1) % entries.size();
	state = State::MOVING;
	updateTargets();
}

void RollingList::setVisible(bool visible)
{
	if (visible)
	{
		state = State::MOVING;
		updateTargets();
	}
	else
	{
		state = State::HIDING;
		updateTargets();
	}
}

void RollingList::update(float deltaTime)
{
	if (state != State::IDLE)
	{
		for (RollingListEntry* t : entries)
		{
			t->update(deltaTime);
		}
	}
}

void RollingList::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (RollingListEntry* t : entries)
	{
		target.draw(t->text, states);
	}
}

RollingList::~RollingList()
{
	for (RollingListEntry* t : entries)
	{
		delete t;
	}
}
