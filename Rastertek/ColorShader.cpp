#include "ColorShader.h"



bool ColorShader::SetShaderParameters(ID3D11DeviceContext * context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&proj, &proj);

	vertexShader->GetMatricesConstantBuffer().Update(context, { world, view, proj });

	return true;
}

void ColorShader::RenderShaders(ID3D11DeviceContext * deviceContext, int indexCount)
{
	vertexShader->Render(deviceContext);
	pixelShader->Render(deviceContext);



	deviceContext->DrawIndexed(indexCount, 0, 0);
}

ColorShader::ColorShader()
{
}


ColorShader::~ColorShader()
{
}

bool ColorShader::Initialize(ID3D11Device * device)
{
	vertexShader = new ColorVertexShader(device);
	pixelShader = new ColorPixelShader(device);
	
	return true;
}

void ColorShader::Shutdown()
{
	delete pixelShader;
	delete vertexShader;
}

bool ColorShader::Render(ID3D11DeviceContext * deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj)
{
	if (!SetShaderParameters(deviceContext, world, view, proj))
		return false;

	RenderShaders(deviceContext, indexCount);

	return true;
}
