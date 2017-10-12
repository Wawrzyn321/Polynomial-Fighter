#include <iostream>
#include <time.h>

using namespace std;

int main() {
	srand((unsigned)time(NULL));

#ifdef  _WIN32
	//hide console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


	system("pause");
	return 0;
}