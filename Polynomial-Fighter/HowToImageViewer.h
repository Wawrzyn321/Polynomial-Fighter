#ifndef HOW_TO_IMAGE_VIEWER_H
#define HOW_TO_IMAGE_VIEWER_H
#include <SFML/Graphics.hpp>
#include <array>
#include "AssetManager.h"

class HowToImageViewer : public sf::Drawable
{
	friend class EasterEgg;
	std::array<AssetManager::TexturePointer, 9> textures;
	sf::Sprite image1;
	sf::Sprite image2;
	int alpha1 = 0;
	int alpha2 = 0;

	int currentImageIndex;

	void loadImages();
public:
	HowToImageViewer(const sf::Vector2f &center);

	void hideAll();

	void show(int index);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
