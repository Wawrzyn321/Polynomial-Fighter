#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "IDamageable.h"
#include "Debug.h"
#include "PolynomialProductForm.h"
#include "PowerfulText.h"
#include "Delegate.h"
#include "EnemyCannon.h"
#include "EnemyPolynomialAdapter.h"

class Player;
class Enemy : public Entity, public IDamageable
{
public:
	enum class State
	{
		CLOSING_IN,
		ARRIVED,
		STOPPED,
	};
private:
	sf::RectangleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f playerPosition;
	float attractionRadiusSqr{};
	State state;

	std::unique_ptr<PowerfulText> caption;
	std::unique_ptr<EnemyCannon> cannon;
	std::shared_ptr<EnemyPolynomialAdapter> polynomial;

	unsigned originalDegree{};

	void initComponents(float angle, PolynomialProductForm pff);
public:
	Delegate<unsigned> DeathEvent;

	Enemy();

	void init(const sf::Vector2f& position, const sf::Vector2f& playerPosition, float speed, PolynomialProductForm pff);

	std::shared_ptr<EnemyPolynomialAdapter> &getPolynomial();

	void invokeDeathEvent();

	void setName(const std::string& name);

	void setState(State state);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(const Time::TimeData &timeData) override;

	void receiveDamage(float damage, float bonusDamageMultiplier) override;

	void receiveDamage(float damage, const sf::Vector2f &incoming, float bonusDamageMultiplier) override;

	Enemy(const Enemy &) = default;

	virtual ~Enemy();

	Enemy(Enemy&&) = default;
private:
	const float enemyCollisionRadius = 10.0f;
	const float enemyInnerRadiusSQR = 180 * 180;
};

#endif