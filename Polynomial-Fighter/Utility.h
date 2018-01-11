#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "Debug.h"
#include <cmath>

const float pi = 3.1415926535f; //TODO: V624 https://www.viva64.com/en/w/V624 The constant 3.1415926535f is being utilized. The resulting value could be inaccurate. Consider ustd::sing the M_PI constant from <math.h>.

unsigned intLenght(int number);

std::string to_stringWithPrecision(float value, int p);

float minAngleDifference(float from, float to);

void centerTextOrigin(sf::Text &textShape);

void setAlpha(sf::Shape &shape, const sf::Uint8 &alpha);

void setAlpha(sf::Sprite &sprite, const sf::Uint8 &alpha);

void setAlpha(sf::Text &text, const sf::Uint8 &alpha);

sf::Color lerp(sf::Color from, sf::Color to, float amount);

float lerpAngle(float from, float to, float t);

sf::FloatRect getCenteredFloatRect(float width, float height, float xShift = 0, float yShift = 0);

void rotateTowards(sf::Transformable& sprite, float angleDeg, float time = 1.0f);

sf::Vector2f getPointOnIntRect(const sf::FloatRect& bounds);

sf::Color colorWithAlpha(const sf::Color &color, int alpha);

#pragma region Template functions

template <typename T, typename R>
float squaredDistance(sf::Vector2<T> a, sf::Vector2<R> b) {
	return (float)(a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

template <typename T>
T lerp(T from, T to, float amount) {
	return from+(to - from)*amount;
}

template <typename T, typename P, typename R>
auto clamp(T value, P min, R max) -> decltype(value*min*max)
{
	return value<min ? min : value>max ? max : value;
}

template <typename T>
T clamp(T value, T min, T max)
{
	return value<min ? min : value>max ? max : value;
}

template <typename T>
T clamp01(T value)
{
	return value < 0 ? 0 : value>1 ? 1 : value;
}

template <typename T>
sf::Vector2<T> vectorNormalize(sf::Vector2<T> vec) {
	float d = sqrt(vec.x*vec.x+vec.y*vec.y);
	vec.x /= d;
	vec.y /= d;
	return vec;
}

template <typename T1, typename T2>
auto lerp(T1 from, T2 to, float amount) -> decltype(typeid(float)*(from + to)) {
	return from + (to - from)*amount;
}

template <typename T, typename R>
sf::Vector2<T> operator*(const sf::Vector2<T> &vec, R a) {
	return sf::Vector2<T>((T)(vec.x*a), (T)(vec.y*a));
}

template <typename T>
void rotateTowards(sf::Transformable &sprite, sf::Vector2<T> target, float time = 1.0f) {
	float from = sprite.getRotation()*pi / 180.0f;
	float to = atan2(sprite.getPosition().y - target.y, sprite.getPosition().x - target.x);

	float xRotation = (1 - time)*std::cos(from) + time*std::cos(to);
	float yRotation = (1 - time)*std::sin(from) + time*std::sin(to);
	float nextRotation = atan2(yRotation, xRotation);

	sprite.setRotation(nextRotation*180.0f/pi);
}

#pragma endregion

#endif