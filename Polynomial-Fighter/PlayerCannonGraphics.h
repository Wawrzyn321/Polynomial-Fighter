#ifndef PLAYER_CANNON_GRAPHICS_H
#define PLAYER_CANNON_GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <memory>


class PlayerCannonGraphics : public sf::Drawable
{
	sf::Text cannon;
	std::shared_ptr<sf::Font> font;
	float rotationAngleModifier;
public:
	PlayerCannonGraphics();

	sf::Vector2f computeMuzzleShift() const;

	void setShoot(const sf::Vector2f &position, float rotation);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(float deltaTime, float rotation);

	void setPosition(const sf::Vector2f &position);

private:
	const unsigned fontSize = 28;
	const float startingRotationAngleModifier = -25;
	const float minAngleDifference = 1.2f;
	const float rotationSpeed = 0.01f;
};

#endif