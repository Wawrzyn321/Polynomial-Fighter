#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "Entity.h"
#include "IDamageable.h"
#include "Delegate.h"
#include "PlayerHealthGUI.h"
#include "PlayerCannon.h"

class RequestValue;
class Player : public Entity, public IDamageable
{
	sf::Text shape;
	std::shared_ptr<sf::Font> font;

	float health{};
	float maxHealth{};
	bool isAlive{};

	std::unique_ptr<PlayerHealthGUI> healthGUI;
	std::unique_ptr<PlayerCannon> cannon;

	float targetRotation = 0;
	bool rotationEventInvoked{};
	void initGraphics();

	void updateRotation(float deltaTime);
public:
	Action DeathEvent;
	Delegate<float> FinishedRotatingEvent;

	explicit Player(const sf::Vector2f &position);

	void setTargetPosition(const sf::Vector2f& position);

	void processConsoleInput(const RequestValue& value, const std::vector<std::shared_ptr<Entity>> &enemies) const;

	bool getAlive() const;

	float getRotation() const;

	void addRounds(int roundsToAdd) const;

	void addHealthCapacity(float additionalCapacity, bool showFleetingText = false);

	void heal(float healthPoints);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f &position) override;

	void update(const Time::TimeData &timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void receiveDamage(float damage, float bonusDamageMultiplier) override;

	void receiveDamage(float damage, const sf::Vector2f &incoming, float bonusDamageMultiplier) override;

	virtual ~Player();
private:
	const float startingHealth = 10.0f;
	const float playerCollisionRadius = 10.0f;
	const unsigned fontSize = 24;
	sf::Vector2f healthGUIPosition = { GameData::WINDOW_SIZE.x*0.03f, GameData::WINDOW_SIZE.y*0.89f };
	sf::Vector2f healthGUISize = { GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f };

};

#endif
