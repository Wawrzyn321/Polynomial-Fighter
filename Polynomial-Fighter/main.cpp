#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Timer.h"

class SoundSegment
{
protected:
	sf::Music music;
	float accumulator = 0;
public:
	float duration = 0;
	std::string path;

	float getAccumulatorRemainder() const
	{
		return accumulator - duration;
	}

	virtual void loadAndPlay()
	{
		accumulator = 0;
		music.openFromFile(path);
		music.play();
	}
	virtual void load()
	{
		accumulator = 0;
		music.openFromFile(path);
	}
	virtual void play(float remainder = 0)
	{
		accumulator += remainder;
		std::cout << "PLAY " << std::endl;
		music.play();
	}
	virtual bool shouldEnd() = 0;
	virtual void reset() = 0;
	virtual void update(const Time::TimeData &deltaTime)
	{
		accumulator += deltaTime.deltaTime.asMicroseconds();
	}
	virtual void handleInterruption() = 0;
	virtual ~SoundSegment() = default;
};

class SingleSoundSegment : public SoundSegment
{
public:
	SingleSoundSegment(std::string path, float duration)
	{
		this->path = path;
		this->duration = duration;
	}

	SingleSoundSegment(const SingleSoundSegment &other)
	{
		this->path = other.path;
		this->duration = other.duration;
		accumulator = 0;
	}

	bool shouldEnd() override
	{
		return accumulator >= duration;
	}

	void handleInterruption() override
	{
		
	}

	void reset() override
	{
		accumulator = 0;
	}
};

class SegmentPlayer : public SoundSegment
{
	std::vector<SoundSegment*> segments;
	SoundSegment* current = nullptr;
	unsigned segmentIndex;
	float accumulator;
	const float waitTime = 1000 * 1000;
	bool loadedNewAlready = false;

	void getNextSegment()
	{
		segmentIndex++;
		if(segmentIndex >= segments.size())
		{
			current = nullptr;
		}
		else
		{
			current = segments[segmentIndex];
		}
	}
public:
	SegmentPlayer(std::vector<SoundSegment*> segments)
	{
		this->segments = segments;

		segmentIndex = 0;
		if (segments.size() > 0)
		{
			current = segments[segmentIndex];
			current->reset();
			current->loadAndPlay();
		}
	}

	void update(const Time::TimeData &timeData)
	{
		if (current != nullptr)
		{
			current->update(timeData);
			if(current->shouldEnd())
			{
				float remainder = current->getAccumulatorRemainder();
				getNextSegment();
				if (current != nullptr)
				{
					current->play(remainder);
				}
				loadedNewAlready = false;
			}

			if (!loadedNewAlready) {
				accumulator += timeData.deltaTime.asMicroseconds();

				if (accumulator > waitTime) {
					if (segments.size() > segmentIndex + 1)
					{
						std::cout << "LOAD " << segmentIndex + 1 << std::endl;
						segments[segmentIndex + 1]->reset();
						segments[segmentIndex + 1]->load();
					}
					loadedNewAlready = true;
					accumulator = 0;
				}
			}

		}
	}
};

struct TestClip
{
	std::string path;
	float duration;
	TestClip(){}
	TestClip(const std::string &path, float duration)
	{
		this->path = path;
		this->duration = duration;
	}
};

class TestSoundPlayer
{
public:
	sf::Music player1;
	sf::Music player2;
	sf::Music *currentPlayer = nullptr;
	TestClip clip;
	float accumulator = 0;
	TestSoundPlayer(TestClip clip)
	{
		this->clip = clip;

		switchPlayer();
		player1.openFromFile(clip.path);
		player2.openFromFile(clip.path);
		currentPlayer->play();
		accumulator = 0;
	}

	void update(const Time::TimeData &deltaTime)
	{
		accumulator += deltaTime.getScaledDeltaTimeInMili();
		if (accumulator >= clip.duration)
		{
			switchPlayer();
			currentPlayer->play();
			accumulator = 0;
		}
	}

	void switchPlayer()
	{
		if (currentPlayer == &player1)
		{
			currentPlayer = &player2;
		}
		else
		{
			currentPlayer = &player1;
		}
	}
};

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "My window");

	//TestSoundPlayer s(TestClip("res/1_130.ogg", 7300));

	SingleSoundSegment s0 = SingleSoundSegment("res/0_120.ogg", 8190 * 1000);

	SingleSoundSegment s1_1 = SingleSoundSegment("res/1_130.ogg", 7435 * 1000);
	SingleSoundSegment s1_2 = SingleSoundSegment("res/1_130.ogg", 7435 * 1000);

	SingleSoundSegment s2_1 = SingleSoundSegment("res/2_140.ogg", 7000 * 1000);
	SingleSoundSegment s2_2 = SingleSoundSegment("res/2_140.ogg", 7000 * 1000);

	SingleSoundSegment s3_1 = SingleSoundSegment("res/3_150.ogg", 6370 * 1000);
	SingleSoundSegment s3_2 = SingleSoundSegment("res/3_150.ogg", 6370 * 1000);

	SingleSoundSegment s4_1 = SingleSoundSegment("res/4_170.ogg", 5710 * 1000);
	SingleSoundSegment s4_2 = SingleSoundSegment("res/4_170.ogg", 5710 * 1000);

	SingleSoundSegment s5_6 = SingleSoundSegment("res/5+6_180.ogg", 5350*2 * 1000);

	SingleSoundSegment s6_1 = SingleSoundSegment("res/6_180.ogg", 5370 * 1000);
	SingleSoundSegment s6_2 = SingleSoundSegment("res/6_180.ogg", 5270 * 1000);

	SingleSoundSegment s7 = SingleSoundSegment("res/7_180.ogg", 5250  * 1000);

	SingleSoundSegment s8_1 = SingleSoundSegment("res/8_180.ogg", 5270 * 1000);
	SingleSoundSegment s8_2 = SingleSoundSegment("res/8_180.ogg", 5270 * 1000);

	SingleSoundSegment s9_1 = SingleSoundSegment("res/9_180.ogg", 5310 * 1000);
	SingleSoundSegment s9_2 = SingleSoundSegment("res/9_180.ogg", 5310 * 1000);

	SingleSoundSegment s10_11_12_180 = SingleSoundSegment("res/10+11+12_180.ogg", 5320 * 3 * 1000);

	SingleSoundSegment s13_180 = SingleSoundSegment("res/13_180.ogg", 5280 * 2 * 1000);

	ListSoundSegment l1 = ListSoundSegment({ &s1_1, &s1_2 });


	const std::vector<SoundSegment*> v {
		/*&s0,
		&s1_1,
		&s1_2,
		&s2_1,
		&s2_2,&s3_1,
		&s3_2,
		&s4_1,
		&s4_2,
		&s5_6,
		&s6_1,
		&s6_2,
		&s7,
		&s8_1,
		&s8_2,
		&s9_1,
		&s9_2,
		&s10_11_12_180,
		&s6_1,
		&s6_2,
		&s13_180,*/
	};
	SegmentPlayer s = SegmentPlayer(v);
	
	auto t = Time::Timer::instance();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		auto td = t->getTimeData();
		//s.update(td);
		s.update(td);
	}



	/*Game g;
	g.run();*/

	return 0;
}
