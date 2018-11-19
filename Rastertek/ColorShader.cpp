#include "ColorShader.h"



bool ColorShader::InitializeShader(ID3D11Device * device, std::wstring filename, ID3D11DeviceChild **output)
{

	return false;
}

void ColorShader::ShutdownShaders()
{
}

bool ColorShader::SetShaderParameters(ID3D11DeviceContext * context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj)
{
	return false;
}

void ColorShader::RenderShaders(ID3D11DeviceContext * deviceContext, int indexCount)
{
}

ColorShader::ColorShader()
{
}


ColorShader::~ColorShader()
{
}

bool ColorShader::Initialize(ID3D11Device * device)
{
	if (!InitializeShader(device, L"ColorVertexShader.cso", (ID3D11DeviceChild**)&vertexShader))
		return false;

	if (!InitializeShader(device, L"ColorPixelShader.cso", (ID3D11DeviceChild**)&pixelShader))
		return false;

	return true;
}

void ColorShader::Shutdown()
{
	ShutdownShaders();
}

bool ColorShader::Render(ID3D11DeviceContext * deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj)
{
	if (!SetShaderParameters(deviceContext, world, view, proj))
		return false;

	RenderShaders(deviceContext, indexCount);

	return true;
}
