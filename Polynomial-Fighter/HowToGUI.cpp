#include "HowToGUI.h"
#include "AssetManager.h"
#include "RollingListEntry.h"
#include "HowToImageViewer.h"
#include "Utility.h"

HowToGUI::HowToGUI(const sf::Vector2f& center, HowToImageViewer* howToViewer)
{
	this->center = center - sf::Vector2f(0, GameData::WINDOW_SIZE.x * 0.05f);
	this->howToViewer = howToViewer;

	font = AssetManager::instance()->getDefaultFont();
	currentlyCentered = 0;
	state = State::HIDING;
}

void HowToGUI::initTexts(const std::vector<std::string> &texts)
{
	for (unsigned i = 0; i < texts.size(); i++)
	{
		entries.push_back(new RollingListEntry(sf::Text(texts[i], *font, fontSize), center));
		centerTextOrigin(entries.back()->text);
	}

	updateTargets();
}

void HowToGUI::moveUp()
{
	RollingList::moveUp();
	howToViewer->show(currentlyCentered);
}

void HowToGUI::moveDown()
{
	RollingList::moveDown();
	howToViewer->show(currentlyCentered);

}
