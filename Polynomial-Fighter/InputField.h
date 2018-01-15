#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Timer.h"
#include "Delegate.h"
#include "PauseController.h"

class InputField : public sf::Drawable
{
	sf::RectangleShape background;
	sf::Text text;
	sf::RectangleShape cursor;
	sf::Vector2f size;
	sf::Vector2f position;
	std::shared_ptr<sf::Font> font;
	PauseController *pauseController;

	void initGraphics();

	static bool isInputCharacterValid(char c);

	void updateCursorPosition();

	const int characterLimit = 11;

	void heartEasterEgg();
public:
	Delegate<const std::string&> OnTextSubmitted;
	bool interactable{};
	InputField(){}
	InputField(const sf::Vector2f &position, const sf::Vector2f &size, PauseController *pauseController);

	void feed(const sf::Event &event);

	void disable();

	void clear();

	void setText(const std::string &text);

	void update(const Time::TimeData& timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Color color_cursor = sf::Color(240, 240, 240, 255);
};

#endif
