#include "DiffuseShader.h"



bool DiffuseShader::SetShaderParameters(ID3D11DeviceContext * context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 lightColor)
{
	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&proj, &proj);

	vertexShader->GetMatricesConstantBuffer().Update(context, { world, view, proj });

	pixelShader->GetLightBuffer().Update(context, { lightColor, lightDirection, 0.0f });

	context->PSSetShaderResources(0, 1, &texture);

	return true;
}

void DiffuseShader::RenderShaders(ID3D11DeviceContext * deviceContext, int indexCount)
{
	vertexShader->Render(deviceContext);
	pixelShader->Render(deviceContext);

	deviceContext->DrawIndexed(indexCount, 0, 0);
}

DiffuseShader::DiffuseShader()
{
}


DiffuseShader::~DiffuseShader()
{
}

bool DiffuseShader::Initialize(ID3D11Device * device)
{
	vertexShader = new DiffuseVertexShader(device);
	pixelShader = new DiffusePixelShader(device);

	return true;
}

void DiffuseShader::Shutdown()
{
	delete pixelShader;
	delete vertexShader;
}

bool DiffuseShader::Render(ID3D11DeviceContext * deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 lightColor)
{
	if (!SetShaderParameters(deviceContext, world, view, proj, texture, lightDirection, lightColor))
		return false;

	RenderShaders(deviceContext, indexCount);

	return true;
}
