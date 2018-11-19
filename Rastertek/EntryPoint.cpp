#include "System.h"


int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, LPWSTR, int) {
	System system;
	if (system.Initialize(hinstance))
	{
		system.Run();
	}
	system.Shutdown();
	return 0;
}