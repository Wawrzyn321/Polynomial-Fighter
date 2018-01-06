#ifndef FLEETING_TEXT_h
#define FLEETING_TEXT_h
#include "Entity.h"
#include "FloatColor.h"

class FleetingText : public Entity
{
	enum class State
	{
		IDLE,
		WAITING,
		MOVING,
	};

	sf::Text text;
	std::shared_ptr<sf::Font> font;
	State state;

	FloatColor currentColor;
	float accumulator{};
	float fadingSpeed{};
	float waitTime{};
	sf::Vector2f velocity;
	bool moveWhileWaiting{};

	void fadeText(float deltaTime);

	void moveText(float deltaTime);
public:

	FleetingText(const std::string& caption, const sf::Vector2f& position, const sf::Color& color, unsigned fontSize);

	void run(float fadingSpeed, const sf::Vector2f &velocity, float waitTime, bool moveWhileWaiting = false);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;
;
	void update(const Time::TimeData& timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif