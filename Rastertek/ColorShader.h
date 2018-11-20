#pragma once

#include "ColorPixelShader.h"
#include "ColorVertexShader.h"


class ColorShader
{
	ColorPixelShader *pixelShader{ nullptr };
	ColorVertexShader *vertexShader{ nullptr };


	bool SetShaderParameters(ID3D11DeviceContext *context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj);
	void RenderShaders(ID3D11DeviceContext *deviceContext, int indexCount);

public:
	ColorShader();
	~ColorShader();

	bool Initialize(ID3D11Device *device);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext,int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj);
};

