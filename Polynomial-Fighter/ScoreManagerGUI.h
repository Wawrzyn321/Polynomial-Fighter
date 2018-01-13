#ifndef SCORE_MANAGER_GUI
#define SCORE_MANAGER_GUI
#include <SFML/Graphics.hpp>
#include "Timer.h"
#include <memory>

class ScoreManagerGUI : public sf::Drawable
{
	sf::RectangleShape backgroundRectangle;
	sf::Text scoreText;
	std::shared_ptr<sf::Font> font;

	sf::Vector2f textPosition;

	float currentPoints{};
	unsigned targetPoints{};
	unsigned stageNo{};
	unsigned fontSize{};

	float accumulator{};

	void updateScoreText();

	void initGraphics(const sf::Vector2f& position, const sf::Vector2f& size);
public:
	ScoreManagerGUI(const sf::Vector2f& position, const sf::Vector2f& size);

	void setTargetPoints(int targetPoints);

	void updateStageNo(unsigned stageNo, unsigned pointsStageFinished = 0);

	void updateScoreToFinal();

	void reset();

	void update(const Time::TimeData& timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif