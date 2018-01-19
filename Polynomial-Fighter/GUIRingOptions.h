#ifndef GUI_OPTIONS_RING_H
#define GUI_OPTIONS_RING_H
#include <array>
#include "GameData.h"
#include "Timer.h"
#include "TextArrows.h"
#include <memory>

class GUIRingOptions : public sf::Drawable
{
public:
	enum class Option
	{
		PLAY,
		HOW_TO,
		HIGHSCORES,
		EXIT,
		AUTHORS,
		SOUND,
	};
private:
	sf::Text *button_play;
	sf::Text *button_howto;
	sf::Text *button_highscores;
	sf::Text *button_exit;
	sf::Text *button_authors;
	sf::Text *button_sound;

	std::shared_ptr<sf::Font> font;
	std::array<sf::Text*, 6> buttons;

	TextArrows *arrows;

	float commonRotation = 0;
	int currentOption = 0;

	float currentPosition = 0;
	bool isUpdatngRotation = false;
	bool isVisible = false;
	bool isExiting = false;
public:
	bool isZoomed = false;
	bool isTransitioningToGame = false;
	GUIRingOptions(const sf::Vector2f &center);

	void handleDistanceMoving(float deltaTime);

	void handleRotating(float deltaTime);

	void handleColoring(float deltaTime);

	void update(const Time::TimeData& timeData);

	void setTransitioningToGame();

	void setExiting();

	void switchRight();

	void switchLeft();

	void setVisible(bool isVisible, bool resetCurrentOption);

	void setSoundOn(bool isOn) const;

	Option getCurrentOption() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	~GUIRingOptions();
private:
	const float radius = GameData::WINDOW_SIZE.x*0.88f;
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.08f);
	const float rotationSpeed = 0.008f;
	const float rotationThreshold = 0.002f;
};

#endif
