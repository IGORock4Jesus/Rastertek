#include "System.h"



bool System::InitializeWindows(int & width, int & height)
{
	ApplicationHandle = this;
	WNDCLASSEX wc{ 0 };
	appName = L"Engine";
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hinstance;
	wc.hIcon = wc.hIconSm = LoadIcon(0, IDI_WINLOGO);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszClassName = appName;
	wc.cbSize = sizeof(wc);

	RegisterClassEx(&wc);

	auto sw = GetSystemMetrics(SM_CXSCREEN);
	auto sh = GetSystemMetrics(SM_CYSCREEN);
	int posX = 0, posY = 0;

	if (FULL_SCREEN) {
		DEVMODE dm{ 0 };
		dm.dmSize = sizeof(dm);
		dm.dmPelsWidth = sw;
		dm.dmPelsHeight = sh;
		dm.dmBitsPerPel = 32;
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
	}
	else {
		posX = (sw - 800) / 2;
		posY = (sh - 600) / 2;
		sw = 800; sh = 600;
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, appName, appName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUPWINDOW, posX, posY, sw, sh, 0, 0, hinstance, 0);

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	ShowCursor(FALSE);

	width = sw;
	height = sh;

	return true;
}

void System::ShutdownWindows()
{
	ShowCursor(TRUE);

	if (FULL_SCREEN)
		ChangeDisplaySettings(0, 0);

	DestroyWindow(hwnd);
	hwnd = 0;

	UnregisterClass(appName, hinstance);
	hinstance = 0;

	ApplicationHandle = 0;
}

LRESULT System::MessageHandler(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch (m)
	{
	case WM_KEYDOWN:
		input.KeyDown((int)w);
		return 0;

	case WM_KEYUP:
		input.KeyUp((int)w);
		return 0;

	default:
		return DefWindowProc(h, m, w, l);
	}
}

bool System::Frame()
{
	if (input.IsKeyDown(VK_ESCAPE))
		return false;

	if (input.IsKeyDown(VK_UP))
		graphics.Camera().Move({ 0, 0, 1 });

	if (input.IsKeyDown(VK_DOWN))
		graphics.Camera().Move({ 0, 0, -1 });

	if (!graphics.Frame())
		return false;

	return true;
}

LRESULT CALLBACK System::WndProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch (m)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		return ApplicationHandle->MessageHandler(h, m, w, l);
	}
}

System::System()
{
}


System::~System()
{
}

bool System::Initialize(HINSTANCE hinstance)
{
	this->hinstance = hinstance;
	int width = 0, height = 0;
	InitializeWindows(width, height);

	input.Initialize();

	auto result = graphics.Initialize(width, height, hwnd);
	if (!result)
		return false;

	return true;
}

void System::Run()
{
	MSG msg{ 0 };
	bool done{ false };
	while (!done)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			auto result = Frame();
			if (!result)
				done = true;
		}
	}
}

void System::Shutdown()
{
	graphics.Shutdown();

	ShutdownWindows();
}
