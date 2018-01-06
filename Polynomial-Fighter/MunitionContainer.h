#ifndef MUNITUON_GUI_H
#define MUNITUON_GUI_H
#include <SFML/Graphics.hpp>
#include <memory>

class Player;
class MunitionContainer : public sf::Drawable
{
	sf::RectangleShape backgroundRectangle;
	sf::Text roundsCountText;
	sf::RectangleShape reloadingRectangle;
	sf::RectangleShape roundGraphic;

	sf::Vector2f fleetingTextsOrigin;
	unsigned fleetingTextFontSize{};

	std::shared_ptr<sf::Font> font;

	int currentNumberOfRounds{};
	float currentReloadPercentage{};

	void addFleetingText(const std::string& caption, const sf::Color& color);

	void initGraphics(const sf::Vector2f& position, const sf::Vector2f& size);

	void refreshUI();

public:
	MunitionContainer(const sf::Vector2f& position, const sf::Vector2f& size);

	bool canShoot(int requiredRounds = 1) const;

	void addRounds(int roundsToAdd);

	void removeRounds(int roundsToRemove);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const int maxNumberOfRounds = 30;
	const int defaultNumberOfRounds = 5;
	const float roundRefillSpeed = 0.0004f;
	sf::Color color_backgroundRectangleInner = sf::Color(63, 63, 63);
	sf::Color color_backgroundRectangle = sf::Color(193, 193, 193);
	sf::Color color_addRounds = sf::Color(63,63,255);
	sf::Color color_removeRounds = sf::Color(255, 159, 159);
};

#endif