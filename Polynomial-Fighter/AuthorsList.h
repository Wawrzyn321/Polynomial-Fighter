#ifndef AUTHORS_GUI_H
#define AUTHORS_GUI_H
#include "RollingList.h"

class RollingListEntry;
class AuthorsList : public RollingList
{
public:
	AuthorsList(const sf::Vector2f &center);

	void initTexts(const std::vector<std::string> &texts) override;
private:
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.04f);
};

#endif
