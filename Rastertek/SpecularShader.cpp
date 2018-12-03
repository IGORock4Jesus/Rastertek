#include "SpecularShader.h"



bool SpecularShader::SetShaderParameters(ID3D11DeviceContext * context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 diffuseColor, D3DXVECTOR4 ambientColor, D3DXVECTOR3 cameraPosition, float specularPower, D3DXVECTOR4 specularColor)
{
	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&proj, &proj);

	vertexShader->GetMatricesConstantBuffer().Update(context, { world, view, proj });

	pixelShader->GetLightBuffer().Update(context, { ambientColor, diffuseColor, lightDirection, specularPower, specularColor });

	vertexShader->GetCameraConstantBuffer().Update(context, { cameraPosition });

	context->PSSetShaderResources(0, 1, &texture);

	return true;
}

void SpecularShader::RenderShaders(ID3D11DeviceContext * deviceContext, int indexCount)
{
	vertexShader->Render(deviceContext);
	pixelShader->Render(deviceContext);

	deviceContext->DrawIndexed(indexCount, 0, 0);
}

SpecularShader::SpecularShader()
{
}


SpecularShader::~SpecularShader()
{
}

bool SpecularShader::Initialize(ID3D11Device * device)
{
	vertexShader = new SpecularVertexShader(device);
	pixelShader = new SpecularPixelShader(device);

	return true;
}

void SpecularShader::Shutdown()
{
	delete pixelShader;
	delete vertexShader;
}

bool SpecularShader::Render(ID3D11DeviceContext * deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 diffuseColor, D3DXVECTOR4 ambientColor, D3DXVECTOR3 cameraPosition, float specularPower, D3DXVECTOR4 specularColor)
{
	if (!SetShaderParameters(deviceContext, world, view, proj, texture, lightDirection, diffuseColor, ambientColor, cameraPosition, specularPower, specularColor))
		return false;

	RenderShaders(deviceContext, indexCount);

	return true;
}
