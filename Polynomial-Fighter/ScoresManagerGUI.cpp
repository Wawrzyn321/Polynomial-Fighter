#include "ScoresManagerGUI.h"

ScoreManagerGUI::ScoreManagerGUI(sf::Vector2f position, unsigned capacity, float scale)
{
	if (capacity < 1 || scale == 0) return;

	this->capacity = capacity;
	int baseFontSize = (int)(32*scale);
	AssetManager *as = AssetManager::instance();
	sf::Font *font = as->getFont(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_FONTS + GameData::FONT_MONOSPACE);

	background = sf::RectangleShape(sf::Vector2f(scale*270, scale*(80 + capacity * 40)));
	background.setFillColor(color_backgroundFill);
	background.setOutlineThickness(2);
	background.setOutlineColor(color_backroundOutline);
	background.setPosition(position);

	titleText = sf::Text("Highscores", *font, (unsigned int)(baseFontSize*1.1));
	centerTextOrigin(titleText);
	titleText.setPosition(position + sf::Vector2f(background.getSize().x / 2, 30 * scale));

	for (unsigned i = 0; i < capacity; i++) {

		std::string text = toString(i + 1) + ". ";
		text += std::string(dots-intLenght(i+1), '.');

		scoresTexts.push_back(sf::Text(text, *font, baseFontSize));
		centerTextOrigin(scoresTexts[i]);
		scoresTexts[i].setFillColor(color_text);
		scoresTexts[i].setPosition(position + sf::Vector2f(background.getSize().x/2, scale * (30+40*(i+1))));
	}
}

unsigned ScoreManagerGUI::getCapacity() {
	return capacity;
}

void ScoreManagerGUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(titleText, states);
	for (unsigned i = 0; i < scoresTexts.size(); i++) {
		target.draw(scoresTexts[i], states);
	}
	
}

void ScoreManagerGUI::updateScores(std::vector<int> &scores) {
	unsigned fills = std::min(capacity, (unsigned)scores.size());
	std::string text;
	for (unsigned i = 0; i < fills; i++) {
		text = toString(i + 1) + ". ";
		text += std::string(dots +2- intLenght(scores[i]) - intLenght(i + 1), '.');
		text += toString(scores[i]);
		scoresTexts[i].setString(text);
		centerTextOrigin(scoresTexts[i]);
	}
}