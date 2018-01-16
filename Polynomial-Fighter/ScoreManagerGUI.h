#ifndef SCORE_MANAGER_GUI
#define SCORE_MANAGER_GUI
#include <SFML/Graphics.hpp>
#include "Timer.h"
#include <memory>
#include "GameData.h"
#include "FlashingText.h"

class ScoreManagerGUI : public sf::Drawable
{
public:
	enum class EthericalTextState
	{
		IDLE,
		DIM,
		AUG,
	};
private:
	sf::RectangleShape backgroundRectangle;
	sf::Text scoreText;
	sf::Text stageText;
	std::shared_ptr<sf::Font> font;

	bool newAlreadyBeaten;
	std::unique_ptr<FlashingText> flashingNewHighscoreText;
	bool bestAlreadyBeaten;
	std::unique_ptr<FlashingText> flashingBestHighscoreText;
	std::tuple<unsigned, unsigned> minMaxScoresTuple;

	sf::Vector2f scoreTextPosition;

	float currentPoints{};
	unsigned targetPoints{};
	unsigned stageNo{};
	unsigned scoreFontSize{};

	EthericalTextState stageTextState;

	float accumulator{};

	void checkHighscores();

	void updateStageText(const Time::TimeData& timeData);

	void updateScoreText(const Time::TimeData& timeData);

	void updateFlashingTexts(const Time::TimeData& timeData) const;

	void initGraphics(const sf::Vector2f& position, const sf::Vector2f& size);
public:
	ScoreManagerGUI(const sf::Vector2f& position, const sf::Vector2f& size);

	void setTargetPoints(int targetPoints, bool showNotification = false);

	void stageFinished(unsigned stageNo);

	void updateScoreToFinal();

	void reset();

	void update(const Time::TimeData& timeData);

	void earlyDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	~ScoreManagerGUI();
private:
	const unsigned stageFontSize = unsigned(GameData::WINDOW_SIZE.x*0.34f);
	const unsigned flashingTextsSize = unsigned(GameData::WINDOW_SIZE.x*0.04f);
	const float stageScalingThreshold = 0.01f;
	const float scalingSpeed = 0.01f;
};


#endif