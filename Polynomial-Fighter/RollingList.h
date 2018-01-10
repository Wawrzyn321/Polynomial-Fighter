#ifndef ROLLING_LIST_H
#define ROLLING_LIST_H
#include <SFML/Graphics.hpp>
#include "RollingListEntry.h"
#include <memory>
#include "GameData.h"

class RollingList : public sf::Drawable
{
public:
	enum class State {
		IDLE,
		HIDING,
		MOVING,
	};
protected:
	State state{};
	std::vector<RollingListEntry*> entries;
	std::shared_ptr<sf::Font> font;
	int currentlyCentered = 0;
	sf::Vector2f center;

	void layNEntriesOut();

	void updateTargets(int delta = 0);

public:

	virtual void initTexts(const std::vector<std::string> &texts) = 0;

	void moveUp();

	void moveDown();

	void setVisible(bool visible);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual ~RollingList();
protected:
	const float positionShift = GameData::WINDOW_SIZE.x*0.4f;
	const float oneEntryShift = GameData::WINDOW_SIZE.x*0.02f;
	const float twoEntriesShift = GameData::WINDOW_SIZE.x*0.05f;
	const float twoEntriesMultiplier = 0.2f;
};

#endif