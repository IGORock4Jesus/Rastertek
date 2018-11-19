#include "Graphics.h"



bool Graphics::Render()
{
	d3d.BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	d3d.EndScene();

	return true;
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

bool Graphics::Initialize(int width, int height, HWND hwnd)
{
	if (!d3d.Initialize(width, height, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCRENN_DEPTH, SCREEN_NEAR))
		return false;

	return true;
}

bool Graphics::Frame()
{
	if (!Render())
		return false;

	return true;
}

void Graphics::Shutdown()
{
	d3d.Shutdown();
}
