#include "PlayerHealthGUI.h"
#include "Utility.h"
#include "Colors.h"
#include "AssetManager.h"

void PlayerHealthGUI::initGraphics(const sf::Vector2f &position, const sf::Vector2f &size)
{
	backgroundRectangle = sf::RectangleShape(size);	
	backgroundRectangle.setFillColor(Colors::backgroundColor);
	backgroundRectangle.setOutlineThickness(size.y*0.1f);
	backgroundRectangle.setOutlineColor(Colors::FIRST);
	backgroundRectangle.setPosition(position);

	healthBar = sf::RectangleShape(size - sf::Vector2f(size.y*0.2f, size.y*0.2f));
	healthBar.setFillColor(Colors::THIRD);
	healthBar.setOrigin(0, healthBar.getSize().y*0.5f);
	healthBar.setPosition(position + sf::Vector2f(size.y*0.1f, size.y*0.5f));

	font = AssetManager::instance()->getDefaultFont();
	text = sf::Text("10.0/10.0", *font, unsigned(size.y*0.6f));
	centerTextOrigin(text);
	text.setFillColor(Colors::textColor);
	text.setPosition(position + sf::Vector2f(size.x*0.5f, size.y*0.333f));
}

PlayerHealthGUI::PlayerHealthGUI(const sf::Vector2f &position, const sf::Vector2f &size, float maxHealth)
{
	this->maxHealth = maxHealth;
	this->health = maxHealth;

	initGraphics(position, size);
	updateHealthGraphics(1.0f);
}

void PlayerHealthGUI::setMaximumHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
	text.scale(GameData::scaleMultiplier, GameData::scaleMultiplier);
}

void PlayerHealthGUI::updateHealthGraphics(float deltaTime)
{
	const float updatingSpeed = 0.01f;

	float healthBarScale = lerp(healthBar.getScale().x, health / maxHealth, deltaTime * updatingSpeed);
	healthBar.setScale(healthBarScale, 1);

	text.setString(to_stringWithPrecision(health, 1) + "/" + to_stringWithPrecision(maxHealth, 1));

	float textScale = text.getScale().x;
	if (abs(textScale - 1) > GameData::minScalingThreshold)
	{
		textScale = lerp(textScale, 1.0f, deltaTime*GameData::unscalingSpeed);
		text.setScale(textScale, textScale);
	}
	else
	{
		text.setScale(1, 1);
	}
}

void PlayerHealthGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(healthBar, states);
	target.draw(text, states);
}
