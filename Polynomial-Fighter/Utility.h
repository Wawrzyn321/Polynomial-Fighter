#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "Asset Manager.h"
#include "Debug.h"
#include "RandomGenerator.h"

const float pi = 3.1415926535f;

unsigned intLenght(int number);

float minAngleDifference(float from, float to);

void centerTextOrigin(sf::Text &textShape);

void setAlpha(sf::Shape &shape, float alpha);

void setAlpha(sf::Sprite &sprite, float alpha);

void setAlpha(sf::Text &text, float alpha);

sf::Color lerp(sf::Color from, sf::Color to, float amount);

sf::FloatRect getCenteredFloatRect(float width, float height, float xShift = 0, float yShift = 0);

void rotateTowards(sf::Transformable& sprite, float angleDeg, float time = 1.0f);

sf::Vector2f getPointOnIntRect(const sf::FloatRect& bounds);

#pragma region Template functions

template <typename T, typename R>
float squaredDistance(sf::Vector2<T> a, sf::Vector2<R> b) {
	return (float)(a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

template <typename T>
T lerp(T from, T to, float amount) {
	return from+(to - from)*amount;
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

template <typename T, typename R>
sf::Vector2<T> operator*(const sf::Vector2<T> &vec, R a) {
	return sf::Vector2<T>((T)(vec.x*a), (T)(vec.y*a));
}

template <typename T>
void rotateTowards(sf::Transformable &sprite, sf::Vector2<T> target, float time = 1.0f) {
	float from = sprite.getRotation()*pi / 180.0f;
	float to = atan2(sprite.getPosition().y - target.y, sprite.getPosition().x - target.x);

	float xRotation = (1 - time)*cos(from) + time*cos(to);
	float yRotation = (1 - time)*sin(from) + time*sin(to);
	float nextRotation = atan2(yRotation, xRotation);

	sprite.setRotation(nextRotation*180.0f/pi);
}

template<class T>
const T& customClamp(const T &x, const T &upper, const T &lower)
{
    return std::min(upper, std::max(x, lower)); //mam stare gcc i nie chce mi sie aktualizowac... na linuksie to trudne
}

#pragma endregion

#endif