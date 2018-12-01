#pragma once
#include "PixelShader.h"
#include "SamplerState.h"
#include "ConstantBuffer.h"
#include <D3DX10.h>


class DiffusePixelShader :
	public PixelShader
{
public:
	struct LightBuffer
	{
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float padding;
	};

private:
	SamplerState *samplerState{ nullptr };
	ConstantBuffer<LightBuffer> constantBuffer;

public:
	DiffusePixelShader(ID3D11Device *device);
	~DiffusePixelShader();

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
	ConstantBuffer<LightBuffer> &GetLightBuffer() { return constantBuffer; }
};

