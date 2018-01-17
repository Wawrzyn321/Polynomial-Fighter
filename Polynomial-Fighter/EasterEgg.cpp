#include "EasterEgg.h"
#include "HowToImageViewer.h"

HowToImageViewer* EasterEgg::viewer = nullptr;
bool EasterEgg::hasAlreadyDoneThat = false;

void EasterEgg::setViewer(HowToImageViewer* v)
{
	viewer = v;
}

void EasterEgg::modifyHowTo()
{
	if (viewer)
	{
		viewer->textures[8] = AssetManager::instance()->getTexture("howto/9fuck.png");
	}
}
