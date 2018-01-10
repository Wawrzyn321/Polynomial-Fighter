#include "HighscoresGUI.h"
#include "AssetManager.h"
#include "Colors.h"

void HighscoresGUI::updateTargets()
{
	if (state == State::MOVING) {

		int indexDec = currentlyCentered - 1;
		if (indexDec < 0)
		{
			indexDec = unsigned(entries.size() - 1);
		}
		unsigned indexInc = (currentlyCentered + 1) % entries.size();

		for (unsigned i = 0; i < unsigned(indexDec); i++)
		{
			entries[i]->targetColor = sf::Color::Transparent;
			entries[i]->targetPosition = center - sf::Vector2f(0.0f, positionShift);
			entries[i]->targetScale = 0.0f;
		}
		entries[indexDec]->targetColor = lerp(sf::Color::Transparent, sf::Color::White, 0.5f);
		entries[indexDec]->targetPosition = center - sf::Vector2f(0.0f, positionShift * 0.5f);
		entries[indexDec]->targetScale = 0.707f;

		entries[currentlyCentered]->targetPosition = center;
		entries[currentlyCentered]->targetColor = Colors::textLitColor;
		entries[currentlyCentered]->targetScale = 1.0f;

		entries[indexInc]->targetColor = lerp(sf::Color::Transparent, sf::Color::White, 0.5f);
		entries[indexInc]->targetPosition = center + sf::Vector2f(0.0f, positionShift * 0.5f);
		entries[indexInc]->targetScale = 0.707;

		for (unsigned i = indexInc + 1; i < entries.size() && i != indexDec; i++)
		{
			entries[i]->targetColor = sf::Color::Transparent;
			entries[i]->targetPosition = center + sf::Vector2f(0.0f, positionShift);
			entries[i]->targetScale = 0.0f;
		}
	}
	else if (state == State::HIDING)
	{
		for (HighscoreEntry* t : entries)
		{
			t->targetPosition = center;
			t->targetScale = 0;
			t->targetColor = sf::Color::Transparent;
		}
	}
}

HighscoresGUI::HighscoresGUI(const sf::Vector2f& center)
{
	this->center = center - sf::Vector2f(0, GameData::WINDOW_SIZE.x * 0.05f);

	font = AssetManager::instance()->getDefaultFont();
	currentlyCentered = 0;
	state = State::HIDING;

	std::vector<int> exe = { 2, 4, 55, 122, 14,12, 123 };
	if (exe.size() == 0)
	{
		entries.push_back(new HighscoreEntry(
			sf::Text("No scores!", *font, fontSize), center));
		centerTextOrigin(entries.back()->text);
	}
	else
	{
		for (unsigned i = 0; i < exe.size(); i++)
		{
			std::string text = std::to_string(i + 1) + ": "+ std::to_string(exe[i]);
			entries.push_back(new HighscoreEntry(sf::Text(text, *font, fontSize), center));
			centerTextOrigin(entries.back()->text);
		}
	}

	updateTargets();
}

void HighscoresGUI::moveUp()
{
	currentlyCentered--;
	if(currentlyCentered < 0)
	{
		currentlyCentered = unsigned(entries.size()) - 1;
	}
	state = State::MOVING;
	updateTargets();
}

void HighscoresGUI::moveDown()
{
	currentlyCentered = (currentlyCentered + 1) % entries.size();
	state = State::MOVING;
	updateTargets();
}

void HighscoresGUI::setVisible(bool visible)
{
	if (visible)
	{
		state = State::MOVING;
		updateTargets();
	}
	else
	{
		state = State::HIDING;
		updateTargets();
	}
}

void HighscoresGUI::update(float deltaTime)
{
	if (state != State::IDLE)
	{
		for (HighscoreEntry* t : entries)
		{
			t->update(deltaTime);
		}
	}
}

void HighscoresGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (HighscoreEntry* t : entries)
	{
		target.draw(t->text, states);
	}
}

HighscoresGUI::~HighscoresGUI()
{
	for (HighscoreEntry* t : entries)
	{
		delete t;
	}
}
