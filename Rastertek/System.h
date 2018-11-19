#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Input.h"
#include "Graphics.h"



class System
{
	HINSTANCE hinstance;
	HWND hwnd;
	LPCWSTR appName;
	Input input;
	Graphics graphics;

	bool InitializeWindows(int &width, int &height);
	void ShutdownWindows();
	LRESULT MessageHandler(HWND h, UINT u, WPARAM w, LPARAM l);
	bool Frame();
	static LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l);

public:
	System();
	~System();

	bool Initialize(HINSTANCE hinstance);
	void Run();
	void Shutdown();
};

static System *ApplicationHandle = 0;
