#include "HowToList.h"
#include "AssetManager.h"
#include "RollingListEntry.h"
#include "HowToImageViewer.h"
#include "Utility.h"

HowToList::HowToList(const sf::Vector2f& center, HowToImageViewer* howToViewer)
{
	this->center = center - sf::Vector2f(0, GameData::WINDOW_SIZE.x * 0.05f);
	this->howToViewer = howToViewer;

	font = AssetManager::instance()->getDefaultFont();
	currentlyCentered = 0;
	state = State::HIDING;
}

void HowToList::initTexts(const std::vector<std::string> &texts)
{
	for (RollingListEntry* e : entries)
	{
		delete e;
	}
	entries.clear();

	for (unsigned i = 0; i < texts.size(); i++)
	{
		entries.push_back(new RollingListEntry(sf::Text(texts[i], *font, fontSize), center));
		centerTextOrigin(entries.back()->text);
	}

	updateTargets();
}

bool HowToList::moveUp()
{
	if (RollingList::moveUp()) {
		howToViewer->show(currentlyCentered);
		return true;
	}
	return false;
}

bool HowToList::moveDown()
{
	if (RollingList::moveDown()) {
		howToViewer->show(currentlyCentered);
		return true;
	}
	return false;
}
