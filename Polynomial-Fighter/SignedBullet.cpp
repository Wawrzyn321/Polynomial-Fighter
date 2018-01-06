#include "SignedBullet.h"
#include "GameData.h"
#include "Enemy.h"
#include <cassert>
#include "EntityManager.h"

void SignedBullet::initGraphics()
{
	const unsigned captionFontSize = 20;
	const unsigned symbolFontSize = 24;

	font = AssetManager::instance()->getDefaultFont();

	std::string captionText = "x = " + std::to_string(load);
	caption = sf::Text(captionText, *font, captionFontSize);
	centerTextOrigin(caption);

	std::string symbols[] = { "+", "-", "/", "*" };
	std::string symbolText = symbols[RandomGenerator::getInt(0, 3)];
	symbol = sf::Text(symbolText, *font, symbolFontSize);
	centerTextOrigin(symbol);
}

void SignedBullet::hitTarget(const std::shared_ptr<Entity>& target)
{
	auto enemy = std::dynamic_pointer_cast<Enemy>(target);
	assert(enemy);	

	int rootsRemovedCount = enemy->decreasePolynomial(load);
	enemy->receiveDamage(1.0f, vectorNormalize(velocity), static_cast<float>(rootsRemovedCount));
}

SignedBullet::SignedBullet(const sf::Vector2f & position, float radius, int load)
{
	this->load = load;
	this->radius = radius;
	collisionRadius = defaultCollisionRadius;
	recipientID = -1;

	name = "SignedBullet";
	bounds = GameData::DEFAULT_BOUNDS;
	tag = GameData::TAG_SIGNED_BULLET;

	initGraphics();
	SignedBullet::setPosition(position);
}

void SignedBullet::setTarget(const std::shared_ptr<Entity> &recipient, float speed)
{
	if (!recipient)
	{
		Debug::PrintErrorFormatted("Bullet::setTarget: recipient is null!\n");
		return;
	}
	this->recipientID = recipient->getId();

	sf::Vector2f currentTargetPosition = recipient->getPosition();
	velocity = vectorNormalize(currentTargetPosition - getPosition()) * speed;
}

sf::Vector2f SignedBullet::getPosition() const
{
	return symbol.getPosition();
}

void SignedBullet::setPosition(const sf::Vector2f& position)
{
	const float captionYShift = -20;

	caption.setPosition(position + sf::Vector2f(0, captionYShift));
	symbol.setPosition(position);
}

void SignedBullet::update(const Time::TimeData &timeData)
{
	setPosition(getPosition() + velocity * timeData.getScaledDeltaTimeInMili());

	symbol.rotate(rotationSpeed*timeData.getScaledDeltaTimeInMili());

	checkCollisions();
	checkBounds();
}

void SignedBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(caption, states);
	target.draw(symbol, states);
}
