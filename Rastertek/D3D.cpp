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

	IDXGIOutput *dxgiOutput;
	if (FAILED(result = dxgiAdapter->EnumOutputs(0, &dxgiOutput)))
		return false;

	UINT numModes;
	if (FAILED(result = dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr)))
		return false;

	auto modeList = new DXGI_MODE_DESC[numModes];

	if (FAILED(result = dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, modeList)))
		return false;

	DXGI_RATIONAL refreshRate;
	for (int i = 0; i < numModes; i++)
	{
		if (modeList[i].Width == width && modeList[i].Height == height) {
			refreshRate = modeList[i].RefreshRate;
		}
	}

	DXGI_ADAPTER_DESC dxgiAdapterDesc;
	if (FAILED(dxgiAdapter->GetDesc(&dxgiAdapterDesc)))
		return false;

	videoCardMemory = dxgiAdapterDesc.DedicatedVideoMemory;
	videoCardDesc = dxgiAdapterDesc.Description;

	delete[] modeList;

	dxgiOutput->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	
	if (vsyncEnabled) {
		swapChainDesc.BufferDesc.RefreshRate = refreshRate;
	}
	else {
		swapChainDesc.BufferDesc.RefreshRate = { 0,1 };
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;

	swapChainDesc.SampleDesc = { 1,0 };

	swapChainDesc.Windowed = !isFullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL featureLevel{ D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(result = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &deviceContext)))
		return false;

	ID3D11Texture2D *backBufferPointer;
	if (FAILED(result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferPointer))))
		return false;

	if (FAILED(result = device->CreateRenderTargetView(backBufferPointer, nullptr, &renderTargetView)))
		return false;
	backBufferPointer->Release();

	D3D11_TEXTURE2D_DESC depthStencilTextureDesc{ 0 };
	depthStencilTextureDesc.Width = width;
	depthStencilTextureDesc.Height = height;
	depthStencilTextureDesc.MipLevels = 1;
	depthStencilTextureDesc.ArraySize = 1;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.SampleDesc = { 1,0 };
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	if (FAILED(result = device->CreateTexture2D(&depthStencilTextureDesc, nullptr, &depthStencilBuffer)))
		return false;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{ 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xff;
	depthStencilDesc.StencilWriteMask = 0xff;

	depthStencilDesc.FrontFace = {
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_INCR,
		D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
		D3D11_COMPARISON_ALWAYS
	};

	depthStencilDesc.BackFace = {
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_DECR,
		D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
		D3D11_COMPARISON_ALWAYS
	};

	if (FAILED(result = device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState)))
		return false;

	deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;

	if (FAILED(result = device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView)))
		return false;

	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

	if (FAILED(result = device->CreateRasterizerState(&rasterizerDesc, &rasterizerState)))
		return false;

	deviceContext->RSSetState(rasterizerState);

	D3D11_VIEWPORT viewport{ 0 };
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, &viewport);


	auto fov = D3DX_PI / 4.0f;
	auto aspect = (float)width / (float)height;

	D3DXMatrixPerspectiveFovLH(&projection, fov, aspect, screenNear, screenDepth);

	D3DXMatrixIdentity(&world);

	D3DXMatrixOrthoLH(&ortho, width, height, screenNear, screenDepth);

	return true;
}

void D3D::Shutdown()
{
	if (swapChain) {
		swapChain->SetFullscreenState(FALSE, 0);
	}

	if (rasterizerState) {
		rasterizerState->Release();
		rasterizerState = nullptr;
	}

	if (depthStencilView) {
		depthStencilView->Release();
		depthStencilView = nullptr;
	}

	if (depthStencilState) {
		depthStencilState->Release();
		depthStencilState = nullptr;
	}

	if (depthStencilBuffer) {
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}

	if (renderTargetView) {
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	if (deviceContext) {
		deviceContext->Release();
		deviceContext = nullptr;
	}

	if (device) {
		device->Release();
		device = nullptr;
	}

	if (swapChain) {
		swapChain->Release();
		swapChain = nullptr;
	}
}

void D3D::BeginScene(float r, float g, float b, float a)
{
	float color[]{ r,g,b,a };

	deviceContext->ClearRenderTargetView(renderTargetView, color);

	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3D::EndScene()
{
	if (vsyncEnabled)
		swapChain->Present(1, 0);
	else
		swapChain->Present(0, 0);
}

ID3D11Device * D3D::GetDevice()
{
	return device;
}

ID3D11DeviceContext * D3D::GetDeviceContext()
{
	return deviceContext;
}

void D3D::GetProjectionMatrix(D3DXMATRIX & out)
{
	out = projection;
}

void D3D::GetOrthoMatrix(D3DXMATRIX & out)
{
	out = ortho;
}

void D3D::GetWorldMatrix(D3DXMATRIX & out)
{
	out = world;
}

void D3D::GetVideoCardinfo(std::wstring & desc, int & memory)
{
	desc = videoCardDesc;
	memory = videoCardMemory;
}
