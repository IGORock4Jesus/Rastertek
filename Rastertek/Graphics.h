#pragma once

#include <Windows.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLE = true;
const float SCRENN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


class Graphics
{
	bool Render();
public:
	Graphics();
	~Graphics();

	bool Initialize(int width, int height, HWND hwnd);
	bool Frame();
	void Shutdown();
};

