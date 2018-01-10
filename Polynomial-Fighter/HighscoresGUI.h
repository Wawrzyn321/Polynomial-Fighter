#ifndef HIGHSCORES_GUI_H
#define HIGHSCORES_GUI_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "Utility.h"

struct HighscoreEntry
{
	sf::Text text;
	sf::Vector2f targetPosition;
	float targetScale;
	sf::Color targetColor;

	HighscoreEntry(sf::Text text, sf::Vector2f targetPosition)
	{
		this->text = text;
		this->targetPosition = targetPosition;

		targetScale = 1;
		targetColor = sf::Color::White;
	}

	void update(float deltaTime)
	{
		deltaTime = clamp01(deltaTime*0.01f);

		text.setPosition(lerp(text.getPosition(), targetPosition, deltaTime));
		float s = lerp(text.getScale().x, targetScale, deltaTime);
		text.setScale(s, s);
		text.setFillColor(lerp(text.getFillColor(), targetColor, deltaTime));
	}
};

class HighscoresGUI : public sf::Drawable
{
public:
	enum class State{
		IDLE,
		HIDING,
		MOVING,
	};
private:
	State state;
	std::vector<HighscoreEntry*> entries;
	std::shared_ptr<sf::Font> font;
	int currentlyCentered = 0;
	sf::Vector2f center;

	void updateTargets();
public:
	HighscoresGUI(const sf::Vector2f &center);

	void moveUp();

	void moveDown();

	void setVisible(bool visible);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	~HighscoresGUI();
private:
	const unsigned fontSize = unsigned(GameData::WINDOW_SIZE.x*0.1f);
	const float positionShift = GameData::WINDOW_SIZE.x*0.4f;
};


#endif