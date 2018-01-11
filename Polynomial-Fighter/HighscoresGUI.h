#ifndef HIGHSCORES_GUI_H
#define HIGHSCORES_GUI_H
#include "RollingList.h"

class RollingListEntry;
class HighscoresGUI : public RollingList
{
public:
	HighscoresGUI(const sf::Vector2f &center);

	void initTexts(const std::vector<std::string> &texts) override;
private:
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.07f);
};


#endif