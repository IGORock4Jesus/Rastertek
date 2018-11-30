#include "TextureShader.h"



bool TextureShader::SetShaderParameters(ID3D11DeviceContext * context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture)
{
	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&proj, &proj);

	vertexShader->GetMatricesConstantBuffer().Update(context, { world, view, proj });

	context->PSSetShaderResources(0, 1, &texture);

	return true;
}

void TextureShader::RenderShaders(ID3D11DeviceContext * deviceContext, int indexCount)
{
	vertexShader->Render(deviceContext);
	pixelShader->Render(deviceContext);

	deviceContext->DrawIndexed(indexCount, 0, 0);
}

TextureShader::TextureShader()
{
}


TextureShader::~TextureShader()
{
}

bool TextureShader::Initialize(ID3D11Device * device)
{
	vertexShader = new TextureVertexShader(device);
	pixelShader = new TexturePixelShader(device);

	return true;
}

void TextureShader::Shutdown()
{
	delete pixelShader;
	delete vertexShader;
}

bool TextureShader::Render(ID3D11DeviceContext * deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture)
{
	if (!SetShaderParameters(deviceContext, world, view, proj, texture))
		return false;

	RenderShaders(deviceContext, indexCount);

	return true;
}
