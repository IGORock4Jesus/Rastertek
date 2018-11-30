#pragma once

#include <D3D11.h>
#include <D3DX10.h>
#include "Texture.h"


class Model
{
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texel;
	};

	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount;
	Texture *texture{ nullptr };


	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext *deviceContext);

	bool LoadTexture(ID3D11Device *device, std::wstring filename);
	void ReleaseTexture();

public:
	Model();
	~Model();

	bool Initialize(ID3D11Device *device, std::wstring textureFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext *deviceContext);
	
	int GetIndexCount();
	auto GetTexture() { return texture->Get(); }
};



