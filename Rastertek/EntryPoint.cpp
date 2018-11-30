#include "System.h"


int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, LPWSTR, int)
{
	try {
		System system;
		if (system.Initialize(hinstance))
		{
			system.Run();
		}
		system.Shutdown();
	}
	catch (std::exception ex) {
		OutputDebugStringA("---------------------------------------\n");
		OutputDebugStringA(ex.what());
		OutputDebugStringA("\n---------------------------------------\n");
	}
	return 0;
}