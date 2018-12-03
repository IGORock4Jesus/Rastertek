#include "Model.h"
#include "Parser.h"


bool Model::InitializeBuffers(ID3D11Device * device)
{
	vertexCount = indexCount = loadedVertices.size();

	int *indices = new int[indexCount];

	for (size_t i = 0; i < vertexCount; i++)
	{
		indices[i] = i;
	}

	D3D11_BUFFER_DESC bufferDesc{ 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;

	D3D11_SUBRESOURCE_DATA subresourceData{ 0 };
	subresourceData.pSysMem = loadedVertices.data();

	if (FAILED(device->CreateBuffer(&bufferDesc, &subresourceData, &vertexBuffer)))
		return false;

	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(int) * indexCount;

	subresourceData.pSysMem = indices;

	if (FAILED(device->CreateBuffer(&bufferDesc, &subresourceData, &indexBuffer)))
		return false;

	delete[] indices;

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

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Model::LoadTexture(ID3D11Device * device, std::wstring filename)
{
	texture = new Texture(device, filename);

	return true;
}

void Model::ReleaseTexture()
{
	if (texture)
	{
		delete texture;
		texture = nullptr;
	}
}

bool Model::LoadModel(std::wstring filename, IConcreteParser<Vertex> *parser)
{
	loadedVertices = parser->Load(filename);
	return true;
}

void Model::ReleaseModel()
{
	loadedVertices = {};
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

bool Model::Initialize(ID3D11Device * device, std::wstring textureFilename, std::wstring modelFilename, IConcreteParser<Vertex> *parser)
{
	if (!LoadModel(modelFilename, parser))
		return false;

	if (!InitializeBuffers(device))
		return false;

	if (!LoadTexture(device, textureFilename))
		return false;

	return true;
}

void Model::Shutdown()
{
	ReleaseTexture();
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
