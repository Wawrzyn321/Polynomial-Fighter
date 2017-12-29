#include "Enemy.h"
#include "PolynomialMultipler.h"
#include <cassert>
#include "APSBuilder.h"
#include "EntityManager.h"
#include "EnemyCannon.h"
#include "ParticleMaster.h"

class ParticleMaster;

void Enemy::initComponents(const std::string &captionText, float angle)
{
	const unsigned textSize = 20;

	shape = sf::RectangleShape({10, 10});
	shape.setOrigin(5, 5);
	shape.setRotation(angle);

	caption = std::make_unique<PowerfulText>(captionText, AssetManager::instance()->getDefaultFont(), textSize);
	caption->center();
}

Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2f &playerPosition, float speed, PolynomialProductForm pff)
{
	this->name = PolynomialMultipler::generalForm(pff).toString();
	this->pff = pff;
	this->playerPosition = playerPosition;
	tag = GameData::TAG_ENEMY;
	state = State::CLOSING_IN;
	attractionRadiusSqr = enemyInnerRadiusSQR + pff.getDeg() * 30 + RandomGenerator::getFloat(-50,50);
	originalDegree = unsigned(pff.getDeg());

	sf::Vector2f dir = vectorNormalize(playerPosition - position);
	velocity = dir * speed;

	initComponents(this->name, atan2f(dir.y, dir.x)*180.0f/pi);
	collisionRadius = enemyCollisionRadius;
	Enemy::setPosition(position);
}

void Enemy::initCannon()
{
	cannon = std::make_unique<EnemyCannon>(this, int(pff.getDeg()));

}

bool Enemy::canBeDamagedBy(int value) const
{
	return pff.isRoot(value);
}

int Enemy::decreasePolynomial(int root)
{
	assert(pff.isRoot(root));
	size_t degBefore = pff.getDeg();
	pff.removeFactorsByRoot(root);
	int difference = int(degBefore - pff.getDeg());
	if (pff.getDeg() == 0) {
		DeathEvent(id);
		setToDelete(true);
	}
	else {
		name = PolynomialMultipler::generalForm(pff).toString();
		caption->rebuild(name);
	}
	return difference;
}

unsigned Enemy::getOriginalDegree() const
{
	return originalDegree;
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
	target.draw(*caption.get(), states);
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
	if (pff.getDeg() != 0) {
		ParticleMaster::addEnemyHitParticles(getPosition(), incoming, bonusDamageMultiplier);
		cannon->resetAccumulator();
	}
	else
	{
		ParticleMaster::addEnemyDestroyedParticles(getPosition(), bonusDamageMultiplier);
	}
}

Enemy::~Enemy() {
	caption.reset();
	cannon.reset();
}

#pragma endregion
