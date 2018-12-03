#pragma once

#include "SpecularPixelShader.h"
#include "SpecularVertexShader.h"


class SpecularShader
{
	SpecularPixelShader *pixelShader{ nullptr };
	SpecularVertexShader *vertexShader{ nullptr };


	bool SetShaderParameters(ID3D11DeviceContext *context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 diffuseColor, D3DXVECTOR4 ambientColor, D3DXVECTOR3 cameraPosition, float specularPower, D3DXVECTOR4 specularColor);
	void RenderShaders(ID3D11DeviceContext *deviceContext, int indexCount);

public:
	SpecularShader();
	~SpecularShader();

	bool Initialize(ID3D11Device *device);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 diffuseColor, D3DXVECTOR4 ambientColor, D3DXVECTOR3 cameraPosition, float specularPower, D3DXVECTOR4 specularColor);
};

