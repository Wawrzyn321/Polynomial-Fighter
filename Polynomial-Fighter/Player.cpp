#include "Player.h"
#include "GameData.h"
#include "Utility.h"

void Player::initGraphics()
{
	shape = sf::RectangleShape({ 30,15 });
	shape.setOrigin(15, 15 * 0.5f);

	//healthGUI = std::make_unique<PlayerHealthGUI>(PlayerHealthGUI({ 300, 300 }, { 200, 30 }, maxHealth));
}

Player::Player(const sf::Vector2f& position)
{
	tag = GameData::TAG_PLAYER;
	name = GameData::NAME_PLAYER;
	health = GameData::PLAYER_STARTING_HEALTH;
	maxHealth = GameData::PLAYER_STARTING_HEALTH;
	collisionRadius = GameData::PLAYER_COLLISION_RADIUS;

	initGraphics();
	setPosition(position);
}

sf::Vector2f Player::getPosition()
{
	return shape.getPosition();
}

void Player::setPosition(sf::Vector2f position)
{
	shape.setPosition(position);
}

void Player::onDestroy()
{
	//healthGUI.release();
}

void Player::update(Time::TimeData timeData)
{
	//healthGUI->updateHealthGraphics(timeData.getScaledDeltaTimeInMili());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	//target.draw(*healthGUI, states);
}

void Player::receiveDamage(float damage, float bonusDamageMultiplier)
{
	Debug::PrintFormatted("(%)", name); //no i to siê nie wywo³uje

	/*health = clamp(health - damage*bonusDamageMultiplier, 0.0f, health);
	healthGUI->health = health;
	if(health==0)
	{
		Time::Timer::instance()->setTimeScale(0);
	}*/
}

void Player::receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier)
{
	Debug::PrintFormatted("(%)", name); //no i to siê nie wywo³uje te¿
	//receiveDamage(damage, bonusDamageMultiplier);
	//todo add effects
}
