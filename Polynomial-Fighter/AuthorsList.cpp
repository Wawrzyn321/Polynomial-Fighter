#include "AuthorsList.h"
#include "AssetManager.h"
#include "Utility.h"

AuthorsList::AuthorsList(const sf::Vector2f& center)
{
	this->center = center - sf::Vector2f(0, GameData::WINDOW_SIZE.x * 0.05f);

	positionShift = GameData::WINDOW_SIZE.x*0.3f;
	font = AssetManager::instance()->getDefaultFont();
	currentlyCentered = 0;
	state = State::HIDING;
}

void AuthorsList::initTexts(const std::vector<std::string> &texts)
{
	for (RollingListEntry* t : entries)
	{
		//czy to nie wywali czegos w powietrze?
		delete t;
	}
	entries.clear();
	if (texts.size() == 0)
	{
		entries.push_back(new RollingListEntry(
			sf::Text("No scores yet!", *font, fontSize), center));
		centerTextOrigin(entries.back()->text);
		entries.back()->text.setPosition(center);
	}
	else
	{
		for (unsigned i = 0; i < texts.size(); i++)
		{
			entries.push_back(new RollingListEntry(sf::Text(texts[i], *font, fontSize), center));
			centerTextOrigin(entries.back()->text);
			entries.back()->text.setPosition(center);
		}
	}

	currentlyCentered = 0;
	updateTargets();
}
