#pragma once

#include <fstream>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3DX11async.h>


class ColorShader
{
	struct Matrices
	{
		D3DXMATRIX world, view, proj;
	};

	ID3D11VertexShader *vertexShader{ nullptr };
	ID3D11PixelShader *pixelShader{ nullptr };
	ID3D11InputLayout *inputLayout{ nullptr };
	ID3D11Buffer *matrixBuffer{ nullptr };


	bool InitializeShader(ID3D11Device *device, std::wstring filename, ID3D11DeviceChild **output);
	void ShutdownShaders();

	bool SetShaderParameters(ID3D11DeviceContext *context, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj);
	void RenderShaders(ID3D11DeviceContext *deviceContext, int indexCount);

public:
	ColorShader();
	~ColorShader();

	bool Initialize(ID3D11Device *device);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext,int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj);
};

