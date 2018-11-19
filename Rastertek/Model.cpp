#include "Model.h"



bool Model::InitializeBuffers(ID3D11Device * device)
{
	vertexCount = 3;
	indexCount = 3;

	Vertex *vertices = new Vertex[vertexCount];

	int *indices = new int[indexCount];

	vertices[0].position = { -1,-1,0 };
	vertices[0].color = { 0,1,0,1 };

	vertices[1].position = { 0,1,0 };
	vertices[1].color = { 0,1,0,1 };

	vertices[2].position = { 1,-1,0 };
	vertices[2].color = { 0,1,0,1 };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	D3D11_BUFFER_DESC bufferDesc{ 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;

	D3D11_SUBRESOURCE_DATA subresourceData{ 0 };
	subresourceData.pSysMem = vertices;

	if (FAILED(device->CreateBuffer(&bufferDesc, &subresourceData, &vertexBuffer)))
		return false;

	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(int) * indexCount;

	subresourceData.pSysMem = indices;

	if (FAILED(device->CreateBuffer(&bufferDesc, &subresourceData, &indexBuffer)))
		return false;

	delete[]indices;
	delete[] vertices;

	return true;
}

void Model::ShutdownBuffers()
{
	if (vertexBuffer) {
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}
	if (indexBuffer) {
		indexBuffer->Release();
		indexBuffer = nullptr;
	}
}

void Model::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Model::Model()
{
	vertexBuffer = nullptr;
	indexBuffer = nullptr;
	vertexCount = 0;
	indexCount = 0;
}


Model::~Model()
{
}

bool Model::Initialize(ID3D11Device * device)
{
	if (!InitializeBuffers(device))
		return false;

	return true;
}

void Model::Shutdown()
{
	ShutdownBuffers();
}

void Model::Render(ID3D11DeviceContext * deviceContext)
{
	RenderBuffers(deviceContext);
}

int Model::GetIndexCount()
{
	return indexCount;
}
