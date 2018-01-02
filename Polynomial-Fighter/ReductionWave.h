#ifndef REDUCTION_WAVE_H
#define REDUCTION_WAVE_H
#include "Entity.h"
#include "Enemy.h"

class ReductionWave : public Entity
{
	sf::CircleShape shape;
	std::vector<std::weak_ptr<Enemy>> enemies;
	int divisor;

	float finalRadius;

	void updateGraphics(float deltaTime);

	void checkDistance();
public:
	ReductionWave(sf::Vector2f &position, int divisor, std::vector<std::shared_ptr<Entity>> enemies);

	void update(const Time::TimeData& timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

private:
	const float radiusDelta = 1.1f;
	const float outlinePercentage = 0.09f;
	sf::Color waveColor = sf::Color(255, 255, 255, 7);
	sf::Color outlineColor = sf::Color(255, 255, 255, 31);
};


#endif