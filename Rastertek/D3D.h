#pragma once

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include <D3D11.h>
#include <D3DX10.h>
#include <string>


class D3D
{
	bool vsyncEnabled;
	int videoCardMemory;
	std::string videoCardDesc;
	IDXGISwapChain *swapChain{ nullptr };
	ID3D11Device *device{ nullptr };
	ID3D11DeviceContext *deviceContext{ nullptr };
	ID3D11RenderTargetView *renderTargetView{ nullptr };
	ID3D11Texture2D *depthStencilBuffer{ nullptr };
	ID3D11DepthStencilState *depthStencilState{ nullptr };
	ID3D11DepthStencilView *depthStencilView{ nullptr };
	ID3D11RasterizerState *rasterizerState{ nullptr };
	D3DXMATRIX projection, world, ortho;


public:
	D3D();
	~D3D();

	bool Initialize(int width, int height, bool vsyncEnabled, HWND hwnd, bool isFullScreen, float screenDepth, float screenNear);
	void Shutdown();

	void BeginScene(float r, float g, float b, float a);
	void EndScene();

	ID3D11Device *GetDevice();
	ID3D11DeviceContext *GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX& out);
	void GetOrthoMatrix(D3DXMATRIX& out);
	void GetWorldMatrix(D3DXMATRIX& out);

	void GetVideoCardinfo(std::string& desc, int& memory);



};

