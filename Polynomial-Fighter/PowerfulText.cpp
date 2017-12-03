#include "PowerfulText.h"
#include <iostream>

PowerfulText::PowerfulText(const std::string& script, const std::shared_ptr<sf::Font> &font, unsigned characterSize)
{
	this->script = script;
	this->font = font;
	this->characterSize = characterSize;
	this->color = sf::Color::White;
	this->position = { 0,0 };

	rebuild(script);
}

void PowerfulText::rebuild(const std::string& script, bool autoRecenter)
{
	auto smallerCharacterSize = static_cast<unsigned>(characterSize * SIZE_MULTIPLIER);
	auto scaledOffset = static_cast<unsigned>(characterSize*MID_TEXT_OFFSET);

	texts.clear();
	overallLength = 0;
	isCentered = false;

	unsigned current = 0;
	unsigned start = 0;

	while (current < script.size())
	{
		const char c = script[current];
		if (c != UPPER && c != LOWER)
		{
			current++;
		}
		else
		{
			texts.emplace_back(script.substr(start, current - start), *font, characterSize);
			texts.back().setOrigin(-overallLength, 0);
			texts.back().setPosition({ 0,0 });
			overallLength += texts.back().getLocalBounds().width + scaledOffset;

			current++;
			if (current == script.size())
			{
				throw std::runtime_error("PowerfulText::rebuild: out of range!");
			}

			texts.emplace_back(script[current], *font, smallerCharacterSize);
			const float yOffset = (c == UPPER ? UPPER_SHIFT : LOWER_SHIFT)*characterSize*SIZE_MULTIPLIER;
			texts.back().setOrigin(-overallLength, yOffset);
			texts.back().setPosition({ 0,0 });
			overallLength += texts.back().getLocalBounds().width + scaledOffset*SIZE_MULTIPLIER;

			current++;
			start = current;
		}
	}

	if (start != current)
	{
		texts.emplace_back(script.substr(start, current - start), *font, characterSize);
		texts.back().setOrigin(-overallLength, 0);
		texts.back().setPosition({ 0,0 });
		overallLength += texts.back().getLocalBounds().width + scaledOffset;
	}

	setColor(color);

	if(autoRecenter)
	{
		center();
	}
	setPosition(getPosition());
}

void PowerfulText::center()
{
	if (isCentered) return;

	for (sf::Text &text : texts)
	{
		text.setOrigin({ text.getOrigin().x + overallLength * 0.5f, text.getOrigin().y });
	}

	isCentered = true;
}

sf::Color PowerfulText::getColor() const
{
	return color;
}

void PowerfulText::setColor(const sf::Color &color)
{
	this->color = color;
	for (sf::Text &text : texts)
	{
		text.setFillColor(color);
	}
}

sf::Vector2f PowerfulText::getPosition() const
{
	return position;
}

void PowerfulText::setPosition(const sf::Vector2f &position)
{
	this->position = position;
	for (sf::Text &text : texts)
	{
		text.setPosition(position);
	}
}

int PowerfulText::getCharacterSize() const
{
	return characterSize;
}

void PowerfulText::setCharacterSize(unsigned characterSize)
{
	this->characterSize = characterSize;

	rebuild(script, true);
	setPosition(position);
}

void PowerfulText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto &text : texts)
	{
		target.draw(text, states);
	}
}
