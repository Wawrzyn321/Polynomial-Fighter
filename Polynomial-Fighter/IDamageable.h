#ifndef IDAMAGEABLE
#define IDAMAGEABLE

class IDamageable {
public:
	virtual void receiveDamage(float damage) = 0;
};


#endif