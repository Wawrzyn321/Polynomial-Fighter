#include "GUILabel.h"
#include "Debug.h"
#include "SoundManager.h"

bool GUILabel::mouseCollideText(sf::Vector2i pos) {
	
	return (pos.x >= text.getGlobalBounds().left
		&& pos.x <= text.getGlobalBounds().left + text.getGlobalBounds().width
		&& pos.y >= text.getGlobalBounds().top
		&& pos.y <= text.getGlobalBounds().top + text.getGlobalBounds().height);
}

void GUILabel::playClick()
{
	SoundManager::instance()->playSound(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_SOUNDS + GameData::SOUND_MENU_CLICK);
}

GUILabel::GUILabel(sf::Vector2f position, int fontSize, std::string caption, std::function<void(void)> function) {

	action = function;

	auto am = AssetManager::instance();
	auto font = am->getFont(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_FONTS + GameData::FONT_REGULAR);

	text = sf::Text(caption, *font, fontSize);
	text.setFillColor(color_text_normal);
	centerTextOrigin(text);
	text.setPosition(position);
}

void GUILabel::update(Time::TimeData timeData)
{
	text.setFillColor(lerp(text.getFillColor(), currentColor, timeData.getScaledDeltaTimeInSec()*50.0f));
}

void GUILabel::updateText(std::string caption)
{
	text.setString(caption);
}

void GUILabel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
}

#pragma region IMouseEventsListener implementation

void GUILabel::onMouseClick(sf::Vector2i mousePosition) {
	if (action != nullptr) {
		if (mouseCollideText(mousePosition)) {
			playClick();
			action();
		}
	}
}

void GUILabel::onMouseMove(sf::Vector2i mousePosition)
{
	if (mouseCollideText(mousePosition)) {
		currentColor = color_text_highlight;
	}
	else {
		currentColor = color_text_normal;
	}
}

#pragma endregion
