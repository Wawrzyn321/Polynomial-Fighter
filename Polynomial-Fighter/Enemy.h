#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "IDamageable.h"
#include "Debug.h"
#include "PolynomialProductForm.h"
#include "PowerfulText.h"
#include "Delegate.h"

class Player;
class Enemy : public Entity, public IDamageable
{
	enum State
	{
		CLOSING_IN,
		ARRIVED,
	};

	sf::RectangleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f playerPosition;
	PolynomialProductForm pff;
	float attractionRadiusSqr;
	std::unique_ptr<PowerfulText> caption;
	State state;

	void initGraphics(const std::string &name, float angle);
public:
	Delegate<unsigned> DeathEvent;

	Enemy(const sf::Vector2f& position, const sf::Vector2f &playerPosition, float speed, PolynomialProductForm pff);

	bool canBeDamagedBy(int value) const;

	void decreasePolynomial(int root);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(Time::TimeData timeData) override;

	void onDestroy() override;

	void receiveDamage(float damage, float bonusDamageMultiplier) override;

	void receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier) override;
};

#endif