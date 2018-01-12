#include "TitleText.h"
#include "Utility.h"
#include "AssetManager.h"
#include "Colors.h"

TitleText::TitleText(const std::string& caption, const sf::Vector2f &position, unsigned fontSize)
{
	font = AssetManager::instance()->getDefaultFont();
	text = sf::Text(caption, *font, fontSize);
	centerTextOrigin(text);
	text.setPosition(position);
	text.setFillColor(Colors::SECOND);

	state = State::IDLE;
}

void TitleText::setStateValues(const sf::Vector2f &pos1, const sf::Vector2f &pos2)
{
	this->pos1 = pos1;
	this->pos2 = pos2;
}

void TitleText::update(float deltaTime)
{
	if (state != State::IDLE) {

		sf::Vector2f dest;
		if (state == State::UP)
		{
			dest = {text.getPosition().x, -GameData::WINDOW_SIZE.y*0.2f};
		}
		else if (state == State::EXITING || state == State::SPLASH)
		{
			dest = pos1;
		}
		else
		{
			dest = pos2;
		}
		sf::Vector2f pos = lerp(text.getPosition(), dest, deltaTime*lerpSpeed);

		text.setPosition(pos);
		
		if(abs(dest.x - pos.x) < vector2Threshold && abs(dest.y - pos.y) < vector2Threshold && state != State::EXITING)
		{
			text.setPosition(dest);
			state = State::IDLE;
		}
	}

	if(state == State::EXITING)
	{
		sf::Vector2f scale = lerp(text.getScale(), { 0,0 }, deltaTime*0.01f);
		text.setScale(scale);
	}
}

void TitleText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}
