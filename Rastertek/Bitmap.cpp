#include "Bitmap.h"
#include <vector>



Bitmap::Bitmap(ID3D11Device * device, int screenWidth, int screenHeight, std::wstring filename, int bitmapWidth, int bitmapHeight)
	: vertexCount{ 0 }, indexCount{ 0 }, screenWidth{ screenWidth }, screenHeight{ screenHeight }, bitmapWidth{ bitmapWidth }, bitmapHeight{ bitmapHeight }, previousPosX{ -1 }, previousPosY{ -1 }
{
	if (!InitializeBuffers(device))
		throw std::exception("Bitmap.InitializeBuffers() - failed");

	if (!LoadTexture(device, filename))
		throw std::exception("Bitmap.LoadTexture() - failed");
}

Bitmap::~Bitmap()
{
	ReleaseTexture();
	ReleaseBuffers();
}

bool Bitmap::Render(ID3D11DeviceContext * deviceContext, int positionX, int positionY)
{
	if(!UpdateBuffers(deviceContext, positionX, positionY))
	return false;

	RenderBuffers(deviceContext);

	return true;
}

bool Bitmap::InitializeBuffers(ID3D11Device * device)
{
	vertexCount = 4;
	indexCount = 6;
	std::vector<Vertex> vertices{ vertexCount };
	std::vector<int> indices{ 0,1,2, 0,2,3 };
	ZeroMemory(vertices.data(), vertexCount * sizeof(Vertex));
	


	D3D11_BUFFER_DESC desc{ 0 };
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(Vertex) * vertexCount;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA sub{ 0 };
	sub.pSysMem = vertices.data();

	if(FAILED(device->CreateBuffer(&desc, &sub, &vertexBuffer)))
	return false;

	desc.ByteWidth = sizeof(int) * indexCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	sub.pSysMem = indices.data();

	if (FAILED(device->CreateBuffer(&desc, &sub, &indexBuffer)))
		return false;


	return true;
}

void Bitmap::ReleaseBuffers()
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

bool Bitmap::UpdateBuffers(ID3D11DeviceContext * deviceContext, int positionX, int positionY)
{
	if (positionX == previousPosX && positionY == previousPosY)
		return true;

	previousPosX = positionX;
	previousPosY = positionY;

	auto left = (float)screenWidth / 2.0f * (-1.0f) + positionX;
	auto right = left + bitmapWidth;
	auto top = (float)screenHeight / 2.0f - positionY;
	auto bottom = top - bitmapHeight;

	std::vector<Vertex> vertices{ vertexCount };

	vertices[0].position = { left,top,0.0f };
	vertices[1].position = { right,top,0.0f };
	vertices[2].position = { right,bottom,0.0f };
	vertices[3].position = { left,bottom,0.0f };

	vertices[0].texel = { 0.0f, 0.0f };
	vertices[1].texel = { 1.0f, 0.0f };
	vertices[2].texel = { 1.0f, 1.0f };
	vertices[3].texel = { 0.0f, 1.0f };

	D3D11_MAPPED_SUBRESOURCE res;
	deviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res);

	memcpy(res.pData, vertices.data(), vertexCount * sizeof(Vertex));

	deviceContext->Unmap(vertexBuffer, 0);

	return true;
}

void Bitmap::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	UINT stride[]{ sizeof(Vertex) };
	UINT offset[]{ 0 };

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, stride, offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Bitmap::LoadTexture(ID3D11Device * device, std::wstring filename)
{
	texture = new Texture(device, filename);
	return true;
}

void Bitmap::ReleaseTexture()
{
	if (texture) {
		delete texture;
		texture = nullptr;
	}
}
