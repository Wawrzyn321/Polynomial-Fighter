#include "PlayerHealthGUI.h"
#include "Utility.h"

void PlayerHealthGUI::initGraphics(const sf::Vector2f &position, const sf::Vector2f &size)
{
	backgroundRectangle = sf::RectangleShape(size);	
	backgroundRectangle.setFillColor(color_backgroundRectangle);
	backgroundRectangle.setOutlineThickness(size.y*0.1f);
	backgroundRectangle.setOutlineColor(color_backgroundRectangleOutline);
	backgroundRectangle.setPosition(position);

	healthBar = sf::RectangleShape(size - sf::Vector2f(size.y*0.2f, size.y*0.2f));
	healthBar.setFillColor(color_healthBar);
	healthBar.setOrigin(0, healthBar.getSize().y*0.5f);
	healthBar.setPosition(position + sf::Vector2f(size.y*0.1f, size.y*0.5f));
}

PlayerHealthGUI::PlayerHealthGUI(const sf::Vector2f &position, const sf::Vector2f &size, float maxHealth)
{
	this->maxHealth = maxHealth;
	this->health = maxHealth;

	initGraphics(position, size);
	updateHealthGraphics(1.0f);
}

void PlayerHealthGUI::updateHealthGraphics(float deltaTime)
{
	const float updatingSpeed = 0.01f;

	float scale = lerp(healthBar.getScale().x, health / maxHealth, deltaTime*updatingSpeed);
	healthBar.setScale(scale, 1);
}

void PlayerHealthGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(healthBar, states);
}
