#include "MunitionContainer.h"
#include "Debug.h"
#include "FleetingText.h"
#include "EntityManager.h"
#include "Colors.h"
#include "AssetManager.h"

MunitionContainer::MunitionContainer(const sf::Vector2f& position, const sf::Vector2f& size)
{
	currentNumberOfRounds = defaultNumberOfRounds;
	currentReloadPercentage = 0;

	initGraphics(position, size);
}

void MunitionContainer::addFleetingText(const std::string& caption, const sf::Color& color)
{
	auto ft = std::make_shared<FleetingText>(caption, fleetingTextsOrigin, color, fleetingTextFontSize);
	ft->run(0.0009f, { 0, -0.02f }, 0);
	EntityManager::instance()->addEntity(ft);
}

void MunitionContainer::refreshUI()
{
	roundsCountText.setString("x" + std::to_string(currentNumberOfRounds));
}

void MunitionContainer::initGraphics(const sf::Vector2f& position, const sf::Vector2f& size)
{
	backgroundRectangle = sf::RectangleShape(size);
	backgroundRectangle.setFillColor(Colors::backgroundColor);
	backgroundRectangle.setOutlineThickness(size.y*0.1f);
	backgroundRectangle.setOutlineColor(Colors::outlineColor);
	backgroundRectangle.setPosition(position);

	reloadingRectangle = sf::RectangleShape({ size.x*0.75f*0.8f, size.y*0.8f });
	reloadingRectangle.setFillColor(Colors::SECOND);
	reloadingRectangle.setOrigin(reloadingRectangle.getSize()*0.5f);
	reloadingRectangle.setPosition(position + sf::Vector2f(size.x*0.5f*0.75f, size.y*0.5f));

	roundGraphic = sf::RectangleShape({size.x*0.05f, size.y*0.5f});
	roundGraphic.setOrigin(roundGraphic.getSize()*0.5f);
	roundGraphic.setFillColor(Colors::SECOND);
	roundGraphic.setPosition(position + sf::Vector2f(size.x*0.85f, size.y*0.5f));

	font = AssetManager::instance()->getDefaultFont();
	roundsCountText = sf::Text("x0", *font, unsigned(size.y*0.35f));
	roundsCountText.setFillColor(Colors::textColor);
	roundsCountText.setPosition(roundGraphic.getPosition()+ sf::Vector2f(size.x*0.03f, size.y*0.01f));

	fleetingTextsOrigin = roundsCountText.getPosition() + sf::Vector2f(size.x*0.05f, size.y*0.01f);
	fleetingTextFontSize = unsigned(roundsCountText.getCharacterSize()*0.9f);

	refreshUI();
}

bool MunitionContainer::canShoot(int requiredRounds) const
{
	return requiredRounds <= currentNumberOfRounds;
}

void MunitionContainer::addRounds(int roundsToAdd)
{
	currentNumberOfRounds = clamp(currentNumberOfRounds + roundsToAdd, 0, maxNumberOfRounds);
	refreshUI();
	addFleetingText("+" + std::to_string(roundsToAdd), color_addRounds);
}

void MunitionContainer::removeRounds(int roundsToRemove)
{
	if (currentNumberOfRounds - roundsToRemove < 0)
	{
		Debug::PrintErrorFormatted("MunitionGUI::decreaseNumberOfRounds: not enough rounds, check the number by MunitionGUI::canShoot!\n");
		return;
	}
	currentNumberOfRounds -= roundsToRemove;
	refreshUI();
	addFleetingText(std::to_string(-roundsToRemove), color_removeRounds);
}

void MunitionContainer::update(float deltaTime)
{
	if (currentNumberOfRounds < maxNumberOfRounds)
	{
		currentReloadPercentage += deltaTime*roundRefillSpeed;
		reloadingRectangle.setScale(currentReloadPercentage, 1.0f);
		if (currentReloadPercentage >= 1.0f)
		{
			currentReloadPercentage -= 1.0f;
			addRounds(1);
		}
	}
}

void MunitionContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(reloadingRectangle);
	target.draw(roundsCountText);
	target.draw(roundGraphic);
}
