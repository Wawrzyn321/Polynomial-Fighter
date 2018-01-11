#include "Utility.h"
#include "RandomGenerator.h"
#include <iomanip>
#include <sstream>

unsigned intLenght(int number) {
	unsigned int l = 0;

	if (number < 0) {
		number = -number;
		l++; //if negative, add 1 for sign
	}

	while (number) {
		l++;
		number /= 10;
	}

	return l;
}

std::string to_stringWithPrecision(float value, int p)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(p) << value;
	return stream.str();
}

float minAngleDifference(float from, float to) {
	float difference = to - from;
	difference = clamp(static_cast<float>(difference - floor(difference / 360.0f) * 360.0f), 0.0f, 360.0f);
	return difference > 180.0f ? difference - 360.0f : difference;
}

void centerTextOrigin(sf::Text & textShape)
{
	textShape.setOrigin(textShape.getLocalBounds().width / 2, textShape.getLocalBounds().height / 2);
}

void setAlpha(sf::Shape &shape, const sf::Uint8 &alpha)
{
	sf::Color c = shape.getFillColor();
	shape.setFillColor(sf::Color(c.r, c.g, c.b, alpha));
}

void setAlpha(sf::Sprite &sprite, const sf::Uint8 &alpha)
{
	sf::Color c = sprite.getColor();
	sprite.setColor(sf::Color(c.r, c.g, c.b, alpha));
}

void setAlpha(sf::Text &text, const sf::Uint8 &alpha) {
	sf::Color c = text.getFillColor();
	text.setFillColor(sf::Color(c.r, c.g, c.b, alpha));
}

sf::Color lerp(sf::Color from, sf::Color to, float amount)
{
	return sf::Color(
		(sf::Uint8)((float)from.r + ((float)to.r - (float)from.r)*amount),
		(sf::Uint8)((float)from.g + ((float)to.g - (float)from.g)*amount),
		(sf::Uint8)((float)from.b + ((float)to.b - (float)from.b)*amount),
		(sf::Uint8)((float)from.a + ((float)to.a - (float)from.a)*amount));
}

sf::FloatRect getCenteredFloatRect(float width, float height, float xShift, float yShift)
{
	float left = (GameData::WINDOW_SIZE.x - width)*0.5f + xShift;
	float top = (GameData::WINDOW_SIZE.y - height)*0.5f + yShift;
	return sf::FloatRect(left, top, width, height);
}

void rotateTowards(sf::Transformable& transformable, float angleDeg, float time)
{
	float from = transformable.getRotation() * pi / 180.0f;
	float to = angleDeg * pi / 180.0f;

	float xRotation = (1 - time) * cos(from) + time * cos(to);
	float yRotation = (1 - time) * sin(from) + time * sin(to);
	float nextRotation = atan2(yRotation, xRotation);

	transformable.setRotation(nextRotation * 180.0f / pi);
}

float lerpAngle(float from, float to, float t)
{
	from *= pi / 180.0f;
	to *= pi / 180.0f;

	float xRotation = (1 - t) * cos(from) + t * cos(to);
	float yRotation = (1 - t) * sin(from) + t * sin(to);

	return atan2(yRotation, xRotation)* 180.0f / pi;
}

sf::Vector2f getPointOnIntRect(const sf::FloatRect& bounds)
{
	bool horizontal = RandomGenerator::getBoolean();
	if(horizontal)
	{
		float latitude = RandomGenerator::getFloat(0, bounds.width);
		bool left = RandomGenerator::getBoolean();
		return { latitude, (left ? 0 : bounds.height) };
	}
	else
	{
		float altitude = RandomGenerator::getFloat(0, bounds.height);
		bool top = RandomGenerator::getBoolean();
		return { (top ? bounds.width : 0), altitude };
	}
}

sf::Color colorWithAlpha(const sf::Color &color, int alpha)
{
	return sf::Color(color.r, color.g, color.b, alpha);
}