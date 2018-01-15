#ifndef FINAL_SCREEN_H
#define FINAL_SCREEN_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "Timer.h"
#include "StopWatch.h"

class FinalScreen : public sf::Drawable
{
public:
	enum class State
	{
		SCORE,
		PROMPT,
		FADEOUT,
	};
private:
	sf::RectangleShape backgroundRectangle;
	sf::Text gameOverText;
	sf::Text maliciousText;
	sf::Text scoreText;
	sf::Text stageText;
	sf::Text killedText;
	sf::Text pressAnyKeyText;
	sf::Text pressEnterText;
	sf::Text pressEscapeText;
	std::shared_ptr<sf::Font> font;
	StopWatch stopWatch;

	bool isFadingIn;
	unsigned score;
	unsigned killedEnemies;
	unsigned stageNo;

	void playDrummies();

	void handleScoreState(float lerpAmount);

	void handlePromptState(float lerpAmount);

	void handleFadeoutState(float lerpAmount);

	void initGraphics();
public:
	State state;

	FinalScreen(unsigned score, unsigned killedEnemies, unsigned stageNo);

	void update(const Time::TimeData& timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	const float lerpingSpeed = 0.007f;
	const sf::Uint8 color256Threshold = 240;
};

#endif	