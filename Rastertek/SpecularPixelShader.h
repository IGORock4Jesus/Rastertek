#pragma once
#include "PixelShader.h"
#include "SamplerState.h"
#include "ConstantBuffer.h"
#include <D3DX10.h>


class SpecularPixelShader :
	public PixelShader
{
public:
	struct LightBuffer
	{
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float specularPower;
		D3DXVECTOR4 specularColor;
	};

private:
	SamplerState *samplerState{ nullptr };
	ConstantBuffer<LightBuffer> constantBuffer;

public:
	SpecularPixelShader(ID3D11Device *device);
	~SpecularPixelShader();

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
	ConstantBuffer<LightBuffer> &GetLightBuffer() { return constantBuffer; }
};

