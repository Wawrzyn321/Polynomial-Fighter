#include "LayoutController.h"

LayoutController::LayoutController(GUILabel * titleText, std::vector<GUILabel*> menuTexts) 
{
	this->titleText = titleText;
	setupTitleTransform(this->titleText);

	float radius = std::min(GameData::WINDOW_SIZE.x, GameData::WINDOW_SIZE.y)*0.5f * 23 / 24.0f;
	
	for (unsigned int i = 0; i < menuTexts.size(); i++) {
		this->menuTexts.push_back(menuTexts[i]);
		setupTextTransform(this->menuTexts.back(), radius, (float)i * 360.0f / (float)menuTexts.size());
	}

	initRing();
}


void LayoutController::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ring, states);
}

void LayoutController::initRing()
{
	float radius = std::min(GameData::WINDOW_SIZE.x, GameData::WINDOW_SIZE.y)*0.5f * 5 / 6.0f;
	ring = sf::CircleShape(radius, 128);
	ring.setFillColor(sf::Color::Transparent);
	ring.setOutlineThickness(30);
	ring.setOutlineColor(color_ring);
	ring.setOrigin(ring.getRadius(), ring.getRadius());
	ring.setPosition(GameData::WINDOW_SIZE.x *0.5f, GameData::WINDOW_SIZE.y *0.5f);
}

void LayoutController::setupTitleTransform(GUILabel * label)
{
	sf::Text* labelText = label->getText();
	centerTextOrigin(*labelText);
	labelText->setPosition(GameData::WINDOW_SIZE.x *0.5f, GameData::WINDOW_SIZE.y  *0.5f);
}

void LayoutController::setupTextTransform(GUILabel * label, float radius, int angle)
{
	const float scale = 0.2f;

	sf::Text* labelText = label->getText();
	labelText->setScale(scale, scale);
	labelText->setOrigin(0, radius/ scale);
	labelText->setPosition(GameData::WINDOW_SIZE.x *0.5f, GameData::WINDOW_SIZE.y  *0.5f);
	labelText->setRotation(angle);
}
