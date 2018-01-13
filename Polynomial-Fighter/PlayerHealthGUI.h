#ifndef PLAYER_HEALTH_GUI
#define PLAYER_HEALTH_GUI
#include <SFML/Graphics.hpp>
#include <memory>

class PlayerHealthGUI : public sf::Drawable
{
	sf::RectangleShape backgroundRectangle;
	sf::RectangleShape healthBar;
	sf::Text text;
	std::shared_ptr<sf::Font> font;

	void initGraphics(const sf::Vector2f& position, const sf::Vector2f& size);

	float maxHealth{};
public:
	float health{};

	PlayerHealthGUI(const sf::Vector2f &position, const sf::Vector2f &size, float maxHealth);

	void addHealth(float healthToAdd);

	void setMaximumHealth(float maxHealth);

	void updateHealthGraphics(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

#endif