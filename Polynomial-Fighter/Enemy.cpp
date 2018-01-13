#include "Enemy.h"
#include "PolynomialMultipler.h"
#include "EntityManager.h"
#include "EnemyCannon.h"
#include "ParticleMaster.h"
#include "AssetManager.h"
#include "SoundManager.h"
#include "Player.h"

void Enemy::initComponents(float angle, const PolynomialProductForm &pff)
{
	const unsigned textSize = 20;

	shape = sf::RectangleShape({10, 10});
	shape.setOrigin(5, 5);
	shape.setRotation(angle);

	caption = std::make_unique<PowerfulText>(PolynomialMultipler::generalForm(pff).toString(), AssetManager::instance()->getDefaultFont(), textSize);
	caption->center();

	polynomial = std::make_shared<EnemyPolynomialAdapter>(this, pff);

	cannon = std::make_unique<EnemyCannon>(this, int(polynomial->getOriginalDegree()));
}

Enemy::Enemy()
{
	this->name = "Unnamed Enemy";
	tag = GameData::TAG_ENEMY;
	DeathEvent.clear();
}

void Enemy::init(const sf::Vector2f& position, const sf::Vector2f &playerPosition, float speed, const PolynomialProductForm &pff)
{
	this->playerPosition = playerPosition;
	this->name = PolynomialMultipler::generalForm(pff).toString();
	state = State::CLOSING_IN;

	attractionRadiusSqr = enemyInnerRadiusSQR + pff.getDeg() * 30 + RandomGenerator::getFloat(-50, 50);
	collisionRadius = enemyCollisionRadius;

	sf::Vector2f dir = vectorNormalize(playerPosition - position);
	velocity = dir * speed;
	initComponents(atan2f(dir.y, dir.x)*180.0f / pi, pff);

	Enemy::setPosition(position);
}

std::shared_ptr<EnemyPolynomialAdapter> &Enemy::getPolynomial()
{
	return polynomial;
}

void Enemy::invokeDeathEvent()
{
	DeathEvent(id);
	setToDelete(true);
}

void Enemy::setName(const std::string& name)
{
	this->name = name;
	caption->rebuild(name);
}

void Enemy::setState(State state)
{
	this->state = state;
}

#pragma region ITransformable

void Enemy::setPosition(const sf::Vector2f& position)
{
	const float captionYShift = -40;

	shape.setPosition(position);
	caption->setPosition(position + sf::Vector2f(0, captionYShift));
}

sf::Vector2f Enemy::getPosition() const
{
	return shape.getPosition();
}

#pragma endregion

#pragma region Entity

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(*caption, states);
}

void Enemy::update(const Time::TimeData &timeData)
{
	if (state == State::CLOSING_IN) {
		setPosition(getPosition() + velocity*timeData.getScaledDeltaTimeInMili());
		if (squaredDistance(getPosition(), playerPosition) < attractionRadiusSqr)
		{
			state = State::ARRIVED;
			cannon->resetAccumulator();
		}
	}
	else if (state == State::ARRIVED)
	{
		cannon->update(timeData.getScaledDeltaTimeInMili());
	}
}

#pragma endregion

#pragma region IDamageable

void Enemy::receiveDamage(float damage, float bonusDamageMultiplier)
{
	cannon->resetAccumulator();
}

void Enemy::receiveDamage(float damage, const sf::Vector2f &incoming, float bonusDamageMultiplier)
{
	if (polynomial->getDeg() != 0) {
		ParticleMaster::addEnemyHitParticles(getPosition(), incoming, bonusDamageMultiplier);
		cannon->resetAccumulator();
		std::string s = Assets::SOUND_ENEMY_HIT;
		s[Assets::SOUND_ENEMY_HIT_REPLACE] = '0' + RandomGenerator::getInt(1, 2);
		SoundManager::instance()->playSound(s, getPosition());
	}
	else
	{
		ParticleMaster::addEnemyDestroyedParticles(getPosition(), bonusDamageMultiplier);
		SoundManager::instance()->playSound(Assets::SOUND_EXPLOSION_SHORT, getPosition());
	}
}

Enemy::~Enemy() {
	caption.reset();
	cannon.reset();
	polynomial.reset();
}

#pragma endregion
