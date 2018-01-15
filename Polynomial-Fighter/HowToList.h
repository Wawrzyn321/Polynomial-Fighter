#ifndef HOW_TO_GUI_H
#define HOW_TO_GUI_H
#include "RollingList.h"
#include "HowToImageViewer.h"

class RollingListEntry;
class HowToList : public RollingList
{
	HowToImageViewer* howToViewer;
public:
	HowToList(const sf::Vector2f &center, HowToImageViewer* howToViewer);

	void initTexts(const std::vector<std::string> &texts) override;

	bool moveUp() override;

	bool moveDown() override;
private:
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.045f);
};

#endif