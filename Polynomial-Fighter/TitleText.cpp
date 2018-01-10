#include "TitleText.h"
#include "Utility.h"
#include "Timer.h"

TitleText::TitleText(const std::string& caption, const sf::Vector2f &position, unsigned fontSize)
{
	font = AssetManager::instance()->getDefaultFont();
	text = sf::Text(caption, *font, fontSize);
	centerTextOrigin(text);
	text.setPosition(position);

	state = TripleState::IDLE;
}

void TitleText::setStateValues(const sf::Vector2f &pos1, const sf::Vector2f &pos2)
{
	this->pos1 = pos1;
	this->pos2 = pos2;
}

void TitleText::update(float deltaTime)
{
	if (state != TripleState::IDLE) {

		sf::Vector2f dest;
		if (state == TripleState::UP)
		{
			dest = {text.getPosition().x, -GameData::WINDOW_SIZE.y*0.2f};
		}
		else if (state == TripleState::EXITING || state == TripleState::MENU)
		{
			dest = pos1;
		}
		else
		{
			dest = pos2;
		}
		sf::Vector2f pos = lerp(text.getPosition(), dest, deltaTime*lerpSpeed);

		text.setPosition(pos);
		
		if(abs(dest.x - pos.x) < lerpThreshold && abs(dest.y - pos.y) < lerpThreshold
			&& state != TripleState::EXITING)
		{
			text.setPosition(dest);
			state = TripleState::IDLE;
		}
	}

	if(state == TripleState::EXITING)
	{
		sf::Vector2f scale = lerp(text.getScale(), { 0,0 }, deltaTime*0.01f);
		text.setScale(scale);
	}
}

void TitleText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}
