#include "HowToGUI.h"
#include "AssetManager.h"
#include "RollingListEntry.h"
#include "RandomGenerator.h"

HowToGUI::HowToGUI(const sf::Vector2f& center)
{
	this->center = center - sf::Vector2f(0, GameData::WINDOW_SIZE.x * 0.05f);

	font = AssetManager::instance()->getDefaultFont();
	currentlyCentered = 0;
	state = State::HIDING;

}

void HowToGUI::initTexts(const std::vector<std::string> &texts)
{
	updateTargets();
}
