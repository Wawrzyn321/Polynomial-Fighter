#ifndef EASTER_EGG_H
#define EASTER_EGG_H

class HowToImageViewer;
class EasterEgg
{
	static HowToImageViewer *viewer;
public:
	static void setViewer(HowToImageViewer *v);

	static bool hasAlreadyDoneThat;

	static void modifyHowTo();
};

#endif