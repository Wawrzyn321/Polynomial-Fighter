#include "InputField.h"
#include <array>
#include <iostream>
#include <string>
#include "GameData.h"
#include "Debug.h"

void InputField::initGraphics()
{
	background = sf::RectangleShape(size);
	background.setPosition(position);
	background.setFillColor(color_fieldBackground);
	background.setOutlineThickness(2);
	background.setOutlineColor(color_fieldOutline);

	AssetManager *am = AssetManager::instance();

	font = am->getFont(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_FONTS + GameData::FONT_REGULAR);
	text = sf::Text("", *font, static_cast<unsigned int>(size.y * 0.64));
	text.setFillColor(color_text_normal);
	text.setPosition(position + sf::Vector2f(size.x / 10, size.y / 10));

	cursor = sf::RectangleShape(sf::Vector2f(size.y*0.3f, size.y*0.09f));
	cursor.setFillColor(color_cursor);

	updateCursorPosition();
}

bool InputField::isInputCharacterValid(char c)
{
	auto allowedCharacters = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'-', ',', ' ', '>', '<'
	};

	return std::find(allowedCharacters.begin(), allowedCharacters.end(), c) != allowedCharacters.end();
}

void InputField::updateCursorPosition()
{
	cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width, text.getPosition().y + size.y*0.64f);
}

InputField::InputField(sf::Vector2f position, sf::Vector2f size)
{
	this->size = size;
	this->position = position;

	initGraphics();

	interactable = true;
}

void InputField::feed(const sf::Event event)
{
	if (!interactable) return;

	if (event.type == sf::Event::TextEntered) {

		char c = event.text.unicode;
		std::string currentText = text.getString();

		//append new character
		if (isInputCharacterValid(c)) {
			if (currentText.size() < characterLimit) {
				text.setString(currentText + c);
			}
		}
		//return - submit
		else if (c == '\r') {
			if (!currentText.empty())
			{
				OnTextSubmitted.invoke(text.getString());
				clear();
			}
		}

		//backspace with left control - wipe out all characters
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				clear();
			}
			//else - remove last character
			else {
				text.setString(currentText.substr(0, currentText.size() - 1));
			}
		}
		updateCursorPosition();
	}
}

void InputField::clear()
{
	text.setString("");
	updateCursorPosition();
}

void InputField::setText(const std::string &TEXT)
{
	text.setString(TEXT);
	updateCursorPosition();
}

void InputField::update(const Time::TimeData& timeData)
{
	if (!interactable) return;

	float alpha = (sin(timeData.elapsedTime.asMicroseconds()*3.0f *Time::MICRO_TO_SEC*timeData.timeScale) + 1) * 128;
	setAlpha(cursor, alpha*0.75f+64);
}

void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(cursor, states);
	target.draw(text, states);
}
