#pragma once

#include <D3D11.h>
#include <D3DX10.h>
#include "Texture.h"
#include <vector>
#include "IParser.h"
#include "Vertex.h"


class Model
{

	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount;
	Texture *texture{ nullptr };
	std::vector<Vertex> loadedVertices;

	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext *deviceContext);

	bool LoadTexture(ID3D11Device *device, std::wstring filename);
	void ReleaseTexture();

	bool LoadModel(std::wstring filename, IConcreteParser<Vertex> *parser);
	void ReleaseModel();

public:
	Model();
	~Model();

	bool Initialize(ID3D11Device *device, std::wstring textureFilename, std::wstring modelFilename, IConcreteParser<Vertex> *parser);
	void Shutdown();
	void Render(ID3D11DeviceContext *deviceContext);

	int GetIndexCount();
	auto GetTexture() { return texture->Get(); }
};



