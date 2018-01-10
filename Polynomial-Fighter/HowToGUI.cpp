#include "HowToGUI.h"
#include "AssetManager.h"

HowToGUI::HowToGUI(const sf::Vector2f& center)
{
	this->center = center;

	font = AssetManager::instance()->getDefaultFont();
	currentlyCentered = 0;
	state = State::HIDING;

	if (entries.size() == 0)
	{
		entries.push_back(new HowToEntry(
			sf::Text("No scores!", *font, 20),
			center, 1));
	}
	else
	{
		std::vector<int> exe = { 1,4,55,122 };
		for (unsigned i = 0; i < exe.size(); i++)
		{
			std::string text = std::to_string(i + 1) + ": " + std::to_string(exe[i]);
			entries.push_back(new HowToEntry(
				sf::Text(text, *font, 20),
				center, 1));
		}
	}
}

void HowToGUI::moveUp()
{
	currentlyCentered--;
	if (currentlyCentered < 0)
	{
		currentlyCentered = unsigned(entries.size());
	}
	state = State::MOVING;
}

void HowToGUI::moveDown()
{
	currentlyCentered = (currentlyCentered + 1) % entries.size();
	state = State::MOVING;
}

void HowToGUI::setVisible(bool visible)
{
	if (visible)
	{
		state = State::MOVING;
	}
	else
	{
		state = State::HIDING;
	}
}

void HowToGUI::update(float deltaTime)
{
	if (state != State::IDLE)
	{
		switch (state) {
		case State::HIDING:
			break;
		case State::MOVING:
			break;
		}

		for (HowToEntry* t : entries)
		{
			t->update(deltaTime);
		}
	}
}

void HowToGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (HowToEntry* t : entries)
	{
		target.draw(t->text, states);
	}
}

HowToGUI::~HowToGUI()
{
	for (HowToEntry* t : entries)
	{
		delete t;
	}
}
