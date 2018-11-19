#pragma once

#include <D3D11.h>
#include <D3DX10.h>


class Model
{
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount;

	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext *deviceContext);

public:
	Model();
	~Model();

	bool Initialize(ID3D11Device *device);
	void Shutdown();
	void Render(ID3D11DeviceContext *deviceContext);
	
	int GetIndexCount();
};



