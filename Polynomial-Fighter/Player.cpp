#include "Player.h"
#include "GameData.h"
#include "Utility.h"

void Player::initGraphics()
{
	shape = sf::RectangleShape({ 30, 15 });
	shape.setOrigin(15, 15 * 0.5f);

	healthGUI = std::make_unique<PlayerHealthGUI>(
		PlayerHealthGUI(
	{ GameData::WINDOW_SIZE.x*0.03f, GameData::WINDOW_SIZE.y*0.89f },
	{ GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f },
			maxHealth));
}

void Player::updateRotation(float deltaTime)
{
	const float min_difference = 1.2f;
	const float speed = 0.015f;

	if (abs(minAngleDifference(shape.getRotation(), targetRotation))>min_difference)
	{
		rotateTowards(shape, targetRotation, deltaTime*speed);
	}
	else if (!rotationEventInvoked2)
	{
		rotationEventInvoked2 = true;
		shape.setRotation(targetRotation);
		FinishedRotatingEvent(targetRotation);
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
	cannon = std::make_unique<PlayerCannon>(PlayerCannon(position, this));
	rotationEventInvoked2 = true;
    FinishedRotatingEvent.add(std::bind(&PlayerCannon::onRotationFinished, cannon.get(), std::placeholders::_1));
}

void Player::setTargetPosition(const sf::Vector2f& position)
{
	rotationEventInvoked2 = false;
	auto diff = position - getPosition();
	if (position.x != getPosition().x && position.y != getPosition().y) {
		targetRotation = atan2(diff.y, diff.x)*180.0f / pi;
	}
}

void Player::appendTargets(const std::vector<DesignatedTarget>& targets) const
{
	cannon->appendTargets(targets);
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
