#pragma once

#include "TexturePixelShader.h"
#include "TextureVertexShader.h"


class TextureShader
{
	TexturePixelShader *pixelShader{ nullptr };
	TextureVertexShader *vertexShader{ nullptr };


	bool SetShaderParameters(ID3D11DeviceContext *context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture);
	void RenderShaders(ID3D11DeviceContext *deviceContext, int indexCount);

public:
	TextureShader();
	~TextureShader();

	bool Initialize(ID3D11Device *device);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj, ID3D11ShaderResourceView *texture);
};

