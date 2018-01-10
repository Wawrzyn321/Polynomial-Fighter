#ifndef HOW_TO_GUI_H
#define HOW_TO_GUI_H
#include "RollingList.h"

class RollingListEntry;
class HowToGUI : public RollingList
{
public:
	HowToGUI(const sf::Vector2f &center);

	void initTexts(const std::vector<std::string> &texts) override;
private:
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.1f);
};


#endif