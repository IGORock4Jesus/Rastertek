#include "D3D.h"



D3D::D3D()
{
}


D3D::~D3D()
{
}

bool D3D::Initialize(int width, int height, bool vsyncEnabled, HWND hwnd, bool isFullScreen, float screenDepth, float screenNear)
{
	this->vsyncEnabled = vsyncEnabled;
	IDXGIFactory *dxgiFactory;

	HRESULT result;
	if (FAILED(result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory))))
		return false;

	IDXGIAdapter *dxgiAdapter;
	if (FAILED(result = dxgiFactory->EnumAdapters(0, &dxgiAdapter)))
		return false;


}

void D3D::Shutdown()
{
}

void D3D::BeginScene(float r, float g, float b, float a)
{
}

void D3D::EndScene()
{
}

ID3D11Device * D3D::GetDevice()
{
	return nullptr;
}

ID3D11DeviceContext * D3D::GetDeviceContext()
{
	return nullptr;
}

void D3D::GetProjectionMatrix(D3DXMATRIX & out)
{
}

void D3D::GetOrthoMatrix(D3DXMATRIX & out)
{
}

void D3D::GetWorldMatrix(D3DXMATRIX & out)
{
}

void D3D::GetVideoCardinfo(std::string & desc, int & memory)
{
}
