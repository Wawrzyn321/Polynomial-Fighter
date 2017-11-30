#ifndef IDAMAGEABLE
#define IDAMAGEABLE

class IDamageable {
public:
	virtual void receiveDamage(float damage, float bonusDamageMultiplier) = 0;

	virtual void receiveDamage(float damage, sf::Vector2f incoming, float bonusDamageMultiplier) = 0;
};


#endif