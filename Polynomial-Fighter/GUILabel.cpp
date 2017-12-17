#include "GUILabel.h"
#include "Debug.h"
#include "SoundManager.h"

bool GUILabel::mouseCollideText(const sf::Vector2i &pos) {
	sf::FloatRect bounds = text.getGlobalBounds();
	return pos.x >= bounds.left
		&& pos.x <= bounds.left + bounds.width
		&& pos.y >= bounds.top
		&& pos.y <= bounds.top + bounds.height;
}

void GUILabel::playClick()
{
	SoundManager::instance()->playSound(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_SOUNDS + GameData::SOUND_MENU_CLICK);
}

GUILabel::GUILabel(sf::Vector2f position, int fontSize, std::string caption, std::function<void(void)> function) {

	action = function;

	auto am = AssetManager::instance();
	auto font = am->getDefaultFont();

	text = sf::Text(caption, *font, fontSize);
	text.setFillColor(color_text_normal);
	centerTextOrigin(text);
	text.setPosition(position);
}

void GUILabel::update(const Time::TimeData &timeData)
{
	text.setFillColor(lerp(text.getFillColor(), currentColor, timeData.getScaledDeltaTimeInSec()*50.0f));
}

void GUILabel::updateText(const std::string &caption)
{
	text.setString(caption);
}

void GUILabel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
}
