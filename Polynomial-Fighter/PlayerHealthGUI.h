#ifndef PLAYER_HEALTH_GUI
#define PLAYER_HEALTH_GUI
#include <SFML/Graphics.hpp>

class PlayerHealthGUI : public sf::Drawable
{
	sf::RectangleShape backgroundRectangle;
	sf::RectangleShape healthBar;

	void initGraphics(const sf::Vector2f& position, const sf::Vector2f& size);
public:
	float health;
	float maxHealth;
	PlayerHealthGUI(const sf::Vector2f &position, const sf::Vector2f &size, float maxHealth);

	void updateHealthGraphics(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
		
private:
	sf::Color color_backgroundRectangle = sf::Color(223, 223, 223);
	sf::Color color_backgroundRectangleOutline = sf::Color(193, 193, 193);
	sf::Color color_healthBar = sf::Color::Red;
};

#endif