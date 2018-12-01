#include "Graphics.h"



bool Graphics::Render()
{
	d3d.BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	camera.Render();

	D3DXMATRIX world, view, proj;
	view = camera.GetViewMatrix();

	d3d.GetWorldMatrix(world);
	d3d.GetProjectionMatrix(proj);


	model.Render(d3d.GetDeviceContext());

	if (!shader.Render(d3d.GetDeviceContext(), model.GetIndexCount(), world, view, proj, model.GetTexture())) {
		return false;
	}

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

	camera.SetPosition({ 0.0f, 0.0f, -4.0f });

	if (!model.Initialize(d3d.GetDevice(), L"test.dds")) {
		MessageBox(nullptr, L"Could not to initialize the model.", 0, MB_OK);
		return false;
	}

	if (!shader.Initialize(d3d.GetDevice())) {
		MessageBox(nullptr, L"Could not to initialize the shader.", 0, MB_OK);
		return false;
	}

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
	model.Shutdown();
	shader.Shutdown();
	d3d.Shutdown();
}
