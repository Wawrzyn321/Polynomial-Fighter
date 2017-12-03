#include "Enemy.h"
#include "PolynomialMultipler.h"
#include <cassert>
#include "APSBuilder.h"
#include "EntityManager.h"

void Enemy::initGraphics(const std::string &name, float angle)
{
	const unsigned textSize = 20;

	shape = sf::RectangleShape({10, 10});
	shape.setOrigin(5, 5);
	shape.setRotation(angle);

	caption = std::make_unique<PowerfulText>(name, AssetManager::instance()->getDefaultFont(), textSize);
	caption->center();
}

Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2f &playerPosition, float speed, PolynomialProductForm pff)
{
	this->name = PolynomialMultipler::generalForm(pff).toString();
	this->pff = pff;
	this->playerPosition = playerPosition;
	tag = GameData::TAG_ENEMY;
	state = CLOSING_IN;
	attractionRadiusSqr = GameData::ENEMY_INNER_RADIUS_SQR + pff.getDeg() * 30 + RandomGenerator::getFloat(-50,50);

	sf::Vector2f dir = vectorNormalize(playerPosition - position);
	velocity = dir * speed;

	initGraphics(this->name, atan2f(dir.y, dir.x)*180.0f/pi);
	collisionRadius = GameData::ENEMY_COLLISION_RADIUS;
	Enemy::setPosition(position);
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

void Enemy::update(Time::TimeData timeData)
{
	if (state == CLOSING_IN) {
		setPosition(getPosition() + velocity);
		if (squaredDistance(getPosition(), playerPosition) < attractionRadiusSqr)
		{
			state = ARRIVED;
		}
	}
	else
	{

	}
}

void Enemy::onDestroy()
{
	caption.release();
}

#pragma endregion

#pragma region IDamageable

void Enemy::receiveDamage(float damage, float bonusDamageMultiplier)
{
	Debug::PrintFormatted("ala");
}

void Enemy::receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier)
{
	/*AdvancedParticleSystem *aps = APSBuilder::startBuilding(getPosition())
		->setMainData(10000, 10)
		->setIntervals(100, 100, 100)
		->setAsCircle(100, 12)
		->finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));*/
}

#pragma endregion
