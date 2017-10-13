#include "ScoresManagerGUI.h"

ScoreManagerGUI::ScoreManagerGUI(sf::Vector2f position, unsigned capacity, float scale)
{
	if (capacity < 1 || scale == 0) return;

	this->capacity = capacity;
	auto baseFontSize = (int)(32*scale);
	auto as = AssetManager::instance();
	auto font = as->getFont(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_FONTS + GameData::FONT_MONOSPACE);

	background = sf::RectangleShape(sf::Vector2f(scale*270, scale*(80 + capacity * 40)));
	background.setFillColor(color_backgroundFill);
	background.setOutlineThickness(2);
	background.setOutlineColor(color_backroundOutline);
	background.setPosition(position);

	titleText = sf::Text("Highscores", *font, (unsigned int)(baseFontSize*1.1));
	centerTextOrigin(titleText);
	titleText.setPosition(position + sf::Vector2f(background.getSize().x / 2, 30 * scale));

	for (unsigned i = 0; i < capacity; i++) {

		std::string text = std::to_string(i + 1) + ". ";
		text += std::string(dots-intLenght(i+1), '.');

		scoresTexts.push_back(sf::Text(text, *font, baseFontSize));
		centerTextOrigin(scoresTexts[i]);
		scoresTexts[i].setFillColor(color_text);
		scoresTexts[i].setPosition(position + sf::Vector2f(background.getSize().x/2, scale * (30+40*(i+1))));
	}
}

unsigned int ScoreManagerGUI::getCapacity() const{
	return capacity;
}

void ScoreManagerGUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(titleText, states);
	for (const auto &scoresText : scoresTexts) {
		target.draw(scoresText, states);
	}
	
}

void ScoreManagerGUI::updateScores(std::vector<int> &scores) {
	unsigned fills = std::min(capacity, (unsigned)scores.size());
	std::string text;
	for (unsigned i = 0; i < fills; i++) {
		text =std::to_string(i + 1) + ". ";
		text += std::string(dots +2- intLenght(scores[i]) - intLenght(i + 1), '.');
		text += std::to_string(scores[i]);
		scoresTexts[i].setString(text);
		centerTextOrigin(scoresTexts[i]);
	}
}