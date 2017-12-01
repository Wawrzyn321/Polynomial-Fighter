#include "Player.h"
#include "GameData.h"
#include "Utility.h"

void Player::initGraphics()
{
	shape = sf::RectangleShape({ 30, 15 });
	shape.setOrigin(15, 15 * 0.5f);

	healthGUI = std::make_unique<PlayerHealthGUI>(PlayerHealthGUI({ 300, 300 }, { 200, 30 }, maxHealth));
}

void Player::updateRotation(float deltaTime)
{
	const float min_difference = 1.2f;
	const float speed = 0.015f;

	if (abs(minAngleDifference(shape.getRotation(), targetRotation))>min_difference)
	{
		rotateTowards(shape, targetRotation, deltaTime*speed);
	}
	else if (!rotationEventInvoked)
	{
		FinishedRotatingEvent(targetRotation);
		rotationEventInvoked = true;
	}
}

Player::Player(const sf::Vector2f& position)
{
	tag = GameData::TAG_PLAYER;
	name = GameData::NAME_PLAYER;
	health = GameData::PLAYER_STARTING_HEALTH;
	maxHealth = GameData::PLAYER_STARTING_HEALTH;
	collisionRadius = GameData::PLAYER_COLLISION_RADIUS;

	initGraphics();
	this->Player::setPosition(position);
	cannon = std::make_unique<PlayerCannon>(PlayerCannon(position));
    FinishedRotatingEvent.add(std::bind(&PlayerCannon::shoot, cannon.get(), std::placeholders::_1));
}

void Player::setTargetPosition(const sf::Vector2f& position)
{
	auto diff = position - getPosition();
	targetRotation = atan2(diff.y, diff.x)*180.0f / pi;
	rotationEventInvoked = false;
}

#pragma region ITransformable

sf::Vector2f Player::getPosition() const
{
	return shape.getPosition();
}

void Player::setPosition(const sf::Vector2f &position)
{
	shape.setPosition(position);
}

#pragma endregion

#pragma region Entity

void Player::onDestroy()
{
	healthGUI.release();
	cannon.release();
}

void Player::update(Time::TimeData timeData)
{
	float deltaTime = timeData.getScaledDeltaTimeInMili();
	cannon->update(deltaTime);
	healthGUI->updateHealthGraphics(deltaTime);
	updateRotation(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(*healthGUI, states);
}

#pragma endregion

#pragma region IDamageable

void Player::receiveDamage(float damage, float bonusDamageMultiplier)
{
	health = clamp(health - damage*bonusDamageMultiplier, 0.0f, health);
	healthGUI->health = health;
	if (health == 0)
	{
		DeathEvent.invoke(0);
	}
}

void Player::receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier)
{
	receiveDamage(damage, bonusDamageMultiplier);
}

#pragma endregion
