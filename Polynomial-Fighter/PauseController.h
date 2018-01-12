#ifndef PAUSE_CONTROLLER_H
#define PAUSE_CONTROLLER_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameData.h"
#include "FloatColor.h"
#include "Timer.h"
#include "Colors.h"
#include "Delegate.h"

class PauseController : public sf::Drawable
{
	enum class Mode
	{
		PAUSING,
		PAUSED,
		UNPAUSING,
		NONE,
	};
	std::shared_ptr<sf::Font> font;
	sf::Text pauseText;
	FloatColor currentColor;
	Mode mode;

	void initGraphics();

	void checkThreshold(float difference);

	void handleColorChange(const sf::Color& color, float deltaTime);
public:
	Delegate<void> OnExitRequested;
	Delegate<void> OnPausingFinished;
	Delegate<void> OnUnpausingFinished;

	PauseController();

	void switchPause();

	void forceSwitchTo(bool pause);

	bool isPaused() const;

	void feed(const sf::Event& event);

	void update(const Time::TimeData &timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.04f);
	const float colorThreshold = 0.07f;
	const float lerpingSpeed = 0.03f;
	sf::Color textColor = colorWithAlpha(Colors::WHITE, 191);
};

#endif