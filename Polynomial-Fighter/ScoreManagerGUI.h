#ifndef SCORE_MANAGER_GUI
#define SCORE_MANAGER_GUI
#include <SFML/Graphics.hpp>
#include "Timer.h"

class ScoreManagerGUI : public sf::Drawable
{

	sf::RectangleShape backgroundRectangle;
	sf::Text scoreText;
	std::shared_ptr<sf::Font> font;

	sf::Vector2f textPosition;

	float currentPoints;
	unsigned targetPoints;
	unsigned stageNo;
	unsigned fontSize;

	float accumulator;

	void updateScoreText();

	void initGraphics(const sf::Vector2f& position, const sf::Vector2f& size);
public:
	ScoreManagerGUI(const sf::Vector2f& position, const sf::Vector2f& size);

	void setTargetPoints(int targetPoints);

	void updateStageNo(unsigned stageNo, unsigned pointsStageFinished = 0);

	void showFinalScore();

	void update(const Time::TimeData& timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	const float fillingSpeed = 0.05f;
	const float unscalingSpeed = 0.01f;
	const float scaleMultiplier = 1.3f;
	const float minScalingThreshold = 0.01f;
	sf::Color color_backgroundRectangleInner = sf::Color(193, 193, 193);
	sf::Color color_backgroundRectangle = sf::Color(63, 63, 63);
	sf::Color color_text = sf::Color(234, 234, 234);
};


#endif