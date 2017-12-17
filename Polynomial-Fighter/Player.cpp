#include "Player.h"
#include "GameData.h"
#include "Utility.h"
#include "EntityManager.h"
#include "APSBuilder.h"
#include "ParticleMaster.h"

void Player::initGraphics()
{
	font = AssetManager::instance()->getDefaultFont();
	shape = sf::Text("(x)", *font, fontSize);
	centerTextOrigin(shape);

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
	else if (!rotationEventInvoked)
	{
		rotationEventInvoked = true;
		shape.setRotation(targetRotation);
		FinishedRotatingEvent(targetRotation);
	}
}

Player::Player(const sf::Vector2f& position)
{
	tag = GameData::TAG_PLAYER;
	name = GameData::NAME_PLAYER;
	health = startingHealth;
	maxHealth = startingHealth;
	collisionRadius = playerCollisionRadius;
	isAlive = true;

	initGraphics();
	cannon = std::make_unique<PlayerCannon>(PlayerCannon(this, position));
	rotationEventInvoked = true;
    FinishedRotatingEvent.add(std::bind(&PlayerCannon::onRotationFinished, cannon.get(), std::placeholders::_1));
	this->Player::setPosition(position);
}

void Player::setTargetPosition(const sf::Vector2f& position)
{
	rotationEventInvoked = false;
	auto diff = position - getPosition();
	if (position.x != getPosition().x && position.y != getPosition().y) {
		targetRotation = atan2(diff.y, diff.x)*180.0f / pi + 90.0f;
	}
}

void Player::appendTargets(const std::vector<int>& values, const std::vector<std::shared_ptr<Entity>> &enemies) const
{
	cannon->appendTargets(values, enemies);
}

bool Player::getAlive() const
{
	return isAlive;
}

float Player::getRotation() const
{
	return shape.getRotation();
}

void Player::addRounds(int roundsToAdd) const
{
	cannon->addRounds(roundsToAdd);
}

#pragma region ITransformable

sf::Vector2f Player::getPosition() const
{
	return shape.getPosition();
}

void Player::setPosition(const sf::Vector2f &position)
{
	shape.setPosition(position);
	cannon->setPosition(position);
}

#pragma endregion

#pragma region Entity

void Player::update(const Time::TimeData &timeData)
{
	float deltaTime = timeData.getScaledDeltaTimeInMili();
	healthGUI->updateHealthGraphics(deltaTime);
	if (isAlive) {
		updateRotation(deltaTime);
		cannon->update(deltaTime);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isAlive) {
		target.draw(shape, states);
	}
	target.draw(*healthGUI, states);
	target.draw(*cannon, states);
}

#pragma endregion

#pragma region IDamageable

void Player::receiveDamage(float damage, float bonusDamageMultiplier)
{
	health = clamp(health - damage*bonusDamageMultiplier, 0.0f, health);
	healthGUI->health = health;
	if (health == 0)
	{
		DeathEvent.invoke();
		isAlive = false;
		collisionsEnabled = false;
		ParticleMaster::addPlayerDestroyedParticles(getPosition(), bonusDamageMultiplier);
	}
}

void Player::receiveDamage(float damage, const sf::Vector2f incoming, float bonusDamageMultiplier)
{
	bool wasDestroyed = (health - damage*bonusDamageMultiplier) <= 0;
	if (!wasDestroyed) {
		ParticleMaster::addPlayerHitParticles(getPosition(), incoming, bonusDamageMultiplier);
	}
	receiveDamage(damage, bonusDamageMultiplier);
}

#pragma endregion

Player::~Player()
{
	healthGUI.reset();
	cannon.reset();
}