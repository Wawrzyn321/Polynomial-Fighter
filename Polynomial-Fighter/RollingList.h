#ifndef ROLLING_LIST_H
#define ROLLING_LIST_H
#include <SFML/Graphics.hpp>
#include "RollingListEntry.h"
#include <memory>
#include "GameData.h"
#include "StopWatch.h"

class RollingList : public sf::Drawable
{
public:
	enum class State {
		IDLE,
		HIDING,
		MOVING,
	};
private:
	StopWatch *delayGuard = nullptr;
	void runDelayGuard(float interval) const;
protected:
	State state{};
	std::vector<RollingListEntry*> entries;
	std::shared_ptr<sf::Font> font;
	int currentlyCentered = 0;
	sf::Vector2f center;

	void layNEntriesOut();

	void updateTargets(int delta = 0);

public:
	bool showLastChild = true;

	RollingList();

	virtual void initTexts(const std::vector<std::string> &texts) = 0;

	virtual bool moveUp();

	virtual bool moveDown();

	void setVisible(bool visible, bool resetCurrentlyCentered = true);

	void update(const Time::TimeData &timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual ~RollingList();
protected:
	float positionShift = GameData::WINDOW_SIZE.x*0.4f;
	const float oneEntryShift = GameData::WINDOW_SIZE.x*0.02f;
	const float twoEntriesShift = GameData::WINDOW_SIZE.x*0.05f;
	const float twoEntriesMultiplier = 0.2f;
private:
	const float defaultGuardInterval = 200;
};

#endif