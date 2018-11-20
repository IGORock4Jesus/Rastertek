#pragma once

#include <D3D11.h>


template <typename T>
class ConstantBuffer
{
	ID3D11Buffer *buffer{ nullptr };

public:
	ConstantBuffer(ID3D11Device *device) {
		D3D11_BUFFER_DESC desc{ 0 };
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(T);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		device->CreateBuffer(&desc, nullptr, &buffer);
	}
	~ConstantBuffer() {
		if (buffer)
			buffer->Release();
	}

	void Update(ID3D11DeviceContext *deviceContext,const T& data, UINT index = 0) {
		D3D11_MAPPED_SUBRESOURCE subresource;
		if (SUCCEEDED(deviceContext->Map(buffer, index, D3D11_MAP_WRITE_DISCARD, 0, &subresource)))
		{
			memcpy(subresource.pData, &data, sizeof(T));
			deviceContext->Unmap(buffer, index);
		}
	}

};

