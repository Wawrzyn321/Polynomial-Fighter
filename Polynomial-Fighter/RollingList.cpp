#include "RollingList.h"
#include "Colors.h"
#include "Utility.h"
#include <cassert>

void RollingList::layNEntriesOut()
{
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
	entries[indexDec]->targetColor = lerp(sf::Color::Transparent, Colors::WHITE, 0.5f);
	entries[indexDec]->targetPosition = center - sf::Vector2f(0.0f, positionShift * 0.5f);
	entries[indexDec]->targetScale = 0.707f;

	entries[currentlyCentered]->targetPosition = center;
	entries[currentlyCentered]->targetColor = Colors::textLitColor;
	entries[currentlyCentered]->targetScale = 1.0f;

	entries[indexInc]->targetColor = lerp(sf::Color::Transparent, Colors::WHITE, 0.5f);
	entries[indexInc]->targetPosition = center + sf::Vector2f(0.0f, positionShift * 0.5f);
	entries[indexInc]->targetScale = 0.707f;

	for (unsigned i = indexInc + 1; i < entries.size() && i != indexDec; i++)
	{
		entries[i]->targetColor = sf::Color::Transparent;
		entries[i]->targetPosition = center + sf::Vector2f(0.0f, positionShift);
		entries[i]->targetScale = 0.0f;
	}
}

void RollingList::updateTargets(int delta)
{
	if (state == State::MOVING) {

		assert(entries.size() != 0);

		if (entries.size() == 1)
		{
			entries[0]->targetColor = Colors::textLitColor;
			entries[0]->targetPosition = center;
			entries[0]->targetScale = 1.0f;
			entries[0]->text.setPosition(center + sf::Vector2f(0.0f, delta * oneEntryShift));
		}
		else if(entries.size() == 2)
		{
			entries[currentlyCentered]->targetColor = Colors::textLitColor;
			entries[currentlyCentered]->targetPosition = center - sf::Vector2f(0.0f, twoEntriesShift*(1 + twoEntriesMultiplier));
			entries[currentlyCentered]->targetScale = 1.0f;

			entries[1-currentlyCentered]->targetColor = colorWithAlpha(Colors::FIRST, 111);
			entries[1-currentlyCentered]->targetPosition = center + sf::Vector2f(0.0f, twoEntriesShift*(1 + twoEntriesMultiplier));
			entries[1-currentlyCentered]->targetScale = 0.7f;
		}
		else
		{
			layNEntriesOut();
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
	updateTargets(-1);
}

void RollingList::moveDown()
{
	currentlyCentered = (currentlyCentered + 1) % entries.size();
	state = State::MOVING;
	updateTargets(1);
}

void RollingList::setVisible(bool visible, bool resetCurrentlyCentered)
{
	state = visible ? State::MOVING : State::HIDING;
	if (resetCurrentlyCentered)
	{
		currentlyCentered = 0;
	}
	updateTargets();
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
