#pragma once

#include <D3D11.h>
#include <D3DX10.h>
#include "Texture.h"
#include <string>


class Bitmap
{
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texel;
	};

	ID3D11Buffer *vertexBuffer{ nullptr }, *indexBuffer{ nullptr };
	size_t vertexCount, indexCount;
	Texture *texture{ nullptr };

	int screenWidth, screenHeight;
	int bitmapWidth, bitmapHeight;
	int previousPosX, previousPosY;


	bool InitializeBuffers(ID3D11Device *device);
	void ReleaseBuffers();
	bool UpdateBuffers(ID3D11DeviceContext *deviceContext, int positionX, int positionY);
	void RenderBuffers(ID3D11DeviceContext *deviceContext);

	bool LoadTexture(ID3D11Device *device, std::wstring filename);
	void ReleaseTexture();

public:
	Bitmap(ID3D11Device *device, int screenWidth, int screenHeight, std::wstring filename, int bitmapWidth, int bitmapHeight);
	~Bitmap();

	bool Render(ID3D11DeviceContext *deviceContext, int positionX, int positionY);
	size_t GetIndexCount() { return indexCount; }
	ID3D11ShaderResourceView *GetTexture() { return texture->Get(); }
};

