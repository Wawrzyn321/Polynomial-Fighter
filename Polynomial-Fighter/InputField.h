#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Asset Manager.h"
#include "Timer.h"
#include "Delegate.h"

class InputField : public sf::Drawable
{
	sf::RectangleShape background;
	sf::Text text;
	sf::RectangleShape cursor;
	sf::Vector2f size;
	sf::Vector2f position;
	std::shared_ptr<sf::Font> font;

	void initGraphics();
	static bool isInputCharacterValid(char c);
	void updateCursorPosition();

	const int characterLimit = 11;
public:
	Delegate<const std::string&> OnTextSubmitted;
	bool interactable;
	InputField(sf::Vector2f position, sf::Vector2f size);

	void feed(sf::Event event);

	void clear();

	void setText(const std::string &text);

	void update(const Time::TimeData& timeData); //resharper tak zaproponowa³, mo¿na to uogólniæ do entities

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Color color_fieldOutline = sf::Color(127, 127, 127);
	sf::Color color_fieldBackground = sf::Color::Black;
	sf::Color color_text_normal = sf::Color::White;
	sf::Color color_text_invalid = sf::Color::Red;
	sf::Color color_text_unavailable = sf::Color(255, 0, 63);
	sf::Color color_cursor = sf::Color(240, 240, 240, 255);
};

#endif
