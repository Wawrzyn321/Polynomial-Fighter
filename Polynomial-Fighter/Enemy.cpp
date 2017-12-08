#include "Enemy.h"
#include "PolynomialMultipler.h"
#include <cassert>
#include "APSBuilder.h"
#include "EntityManager.h"
#include "EnemyCannon.h"

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

void Enemy::decreasePolynomial(int root)
{
	assert(pff.isRoot(root));
	pff.removeFactorsByRoot(root);

	if (pff.getDeg() == 0) {
		DeathEvent(id);
		setToDelete(true);
	}
	else {
		name = PolynomialMultipler::generalForm(pff).toString();
		caption->rebuild(name);
	}
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
	else
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

void Enemy::receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier)
{
	/*AdvancedParticleSystem *aps = APSBuilder::startBuilding(getPosition())
		->setMainData(10000, 10)
		->setIntervals(100, 100, 100)
		->setAsCircle(100, 12)
		->finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));*/
	cannon->resetAccumulator();
}

#pragma endregion

Enemy::~Enemy() {
	caption.reset();
	cannon.reset();
}