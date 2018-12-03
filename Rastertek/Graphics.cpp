#include "Graphics.h"
#include "OpenFileDialog.h"
#include "ObjParser.h"


bool Graphics::Render(float rotate)
{
	d3d.BeginScene(1.0f, 1.0f, 1.0f, 1.0f);

	camera.Render();

	D3DXMATRIX world, view, proj, ortho;
	view = camera.GetViewMatrix();

	d3d.GetWorldMatrix(world);
	d3d.GetProjectionMatrix(proj);
	d3d.GetOrthoMatrix(ortho);

	D3DXMatrixRotationY(&world, rotate);

	model.Render(d3d.GetDeviceContext());

	if (!shader.Render(d3d.GetDeviceContext(), model.GetIndexCount(), world, view, proj, model.GetTexture(), light.GetDirection(), light.GetDiffuse(), light.GetAmbient(), camera.GetPosition(), light.GetPower(), light.GetSpecular())) {
		return false;
	}

	d3d.TurnZBufferOff();

	D3DXMatrixIdentity(&world);
	bitmap->Render(d3d.GetDeviceContext(), 400, 200);

	textureShader.Render(d3d.GetDeviceContext(), bitmap->GetIndexCount(), world, view, ortho, bitmap->GetTexture());

	d3d.TurnZBufferOn();

	d3d.EndScene();

	return true;
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

bool Graphics::Initialize(HINSTANCE hinstance, int width, int height, HWND hwnd)
{
	if (!d3d.Initialize(width, height, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCRENN_DEPTH, SCREEN_NEAR))
		return false;


	camera.SetPosition({ 0.0f, 30.0f, -100.0f });

	//OpenFileDialog dialog{ hinstance, hwnd };
	//dialog.SetFilter(L"Image Files\0*.jpg;*.png;*.dds\0\0");
	//if (!dialog.ShowDialog())
	//	return false;
	auto textureFilename = L"test.dds"; // dialog.GetFilename();

	////dialog.SetFilter(L"Simple Text Vertex Format\0*.txt\0\0");
	//dialog.SetFilter(L"3DS Max Objects\0*.obj\0\0");
	//if (!dialog.ShowDialog())
	//	return false;

	auto modelFilename = L"teapot.obj"; // dialog.GetFilename();

	ObjParser parser;

	if (!model.Initialize(d3d.GetDevice(), textureFilename, modelFilename, &parser)) {
		MessageBox(nullptr, L"Could not to initialize the model.", 0, MB_OK);
		return false;
	}

	if (!shader.Initialize(d3d.GetDevice())) {
		MessageBox(nullptr, L"Could not to initialize the shader.", 0, MB_OK);
		return false;
	}

	if (!textureShader.Initialize(d3d.GetDevice())) {
		MessageBox(nullptr, L"Could not to initialize the texture shader.", 0, MB_OK);
		return false;
	}

	light.SetAmbient({ 0.15f, 0.15f, 0.15f, 1.0f });
	light.SetDiffuse({ 1,1,1,1 });
	light.SetDirection({ 0,0,1 });
	light.SetSpecular({ 1.0f, 1.0f, 1.0f, 1.0f });
	light.SetPower(32.0f);


	bitmap = new Bitmap(d3d.GetDevice(), width, height, L"glass.jpg", 256, 256);

	return true;
}

bool Graphics::Frame()
{
	rotation += D3DX_PI * 0.005f;
	if (rotation >= 360.0f)
		rotation -= 360.0f;

	if (!Render(rotation))
		return false;

	return true;
}

void Graphics::Shutdown()
{
	if (bitmap) {
		delete bitmap;
		bitmap = nullptr;
	}
	model.Shutdown();
	shader.Shutdown();
	textureShader.Shutdown();
	d3d.Shutdown();
}
