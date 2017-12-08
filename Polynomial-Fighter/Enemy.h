#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "IDamageable.h"
#include "Debug.h"
#include "PolynomialProductForm.h"
#include "PowerfulText.h"
#include "Delegate.h"
#include "EnemyCannon.h"

class Player;
class Enemy : public Entity, public IDamageable
{
	enum class State
	{
		CLOSING_IN,
		ARRIVED,
	};

	sf::RectangleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f playerPosition;
	float attractionRadiusSqr;
	State state;

	PolynomialProductForm pff;
	std::unique_ptr<PowerfulText> caption;
	std::unique_ptr<EnemyCannon> cannon;

	void initComponents(const std::string &captionText, float angle);
public:
	Delegate<unsigned> DeathEvent;

	Enemy(const sf::Vector2f& position, const sf::Vector2f &playerPosition, float speed, PolynomialProductForm pff);

	void initCannon();

	bool canBeDamagedBy(int value) const;

	void decreasePolynomial(int root);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(const Time::TimeData &timeData) override;

	void receiveDamage(float damage, float bonusDamageMultiplier) override;

	void receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier) override;

	Enemy(const Enemy &) = default;

	~Enemy(); 

	Enemy(Enemy&&) = default;
private:
	const float enemyCollisionRadius = 10.0f;
	const float enemyInnerRadiusSQR = 180 * 180;
};

#endif