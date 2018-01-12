#include "HowToImageViewer.h"
#include "Utility.h"

void HowToImageViewer::loadImages()
{
	std::array<std::string, 9> names = 
	{
		"1polynomial.png", "2roots.png", "3form.png",
		"4inequality.png", "5infinite.png", "6reduce.png",
		"7between.png", "8pause.png", "9luck.png"
	};
	for (unsigned i = 0; i < names.size(); i++)
	{	
		textures[i] = AssetManager::instance()->getTexture(GameData::PATH_TO_HOW_TO + names[i]);
	}
}

HowToImageViewer::HowToImageViewer(const sf::Vector2f &center)
{
	currentImageIndex = 0;

	loadImages();

	sf::Vector2f origin = { textures[0]->getSize().x*0.5f, textures[0]->getSize().y*0.5f };
	sf::Vector2f position = center - sf::Vector2f(GameData::WINDOW_SIZE.x*0.3f, 0);
	image1.setOrigin(origin);
	image1.setPosition(position);
	image2.setOrigin(origin);
	image2.setPosition(position);
}

void HowToImageViewer::hideAll()
{
	alpha1 = 0;
	alpha2 = 0;
}

void HowToImageViewer::show(int index)
{
	if (alpha1 == 0)
	{
		alpha1 = 255;
		alpha2 = 0;
		image1.setTexture(*textures[index]);
		image2.setTexture(*textures[currentImageIndex]);
	}
	else
	{
		alpha1 = 0;
		alpha2 = 255;
		image1.setTexture(*textures[currentImageIndex]);
		image2.setTexture(*textures[index]);
	}

	currentImageIndex = index;
}

void HowToImageViewer::update(float deltaTime)
{
	deltaTime = clamp01(deltaTime);
	deltaTime *= 0.1f;

	float newAlpha1 = lerp(float(image1.getColor().a), float(alpha1), deltaTime);
	float newAlpha2 = lerp(float(image2.getColor().a), float(alpha2), deltaTime);
	setAlpha(image1, int(newAlpha1));
	setAlpha(image2, int(newAlpha2));
}

void HowToImageViewer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(image1, states);
	target.draw(image2, states);
}
