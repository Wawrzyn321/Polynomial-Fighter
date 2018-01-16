#ifndef EASTER_EGG_H
#define EASTER_EGG_H
#include <memory>

class HowToImageViewer;
class EasterEgg
{
	static std::shared_ptr<HowToImageViewer> viewer;
public:
	static void setViewer(const std::shared_ptr<HowToImageViewer> &v);

	static bool hasAlreadyDoneThat;

	static void modifyHowTo();
};

#endif