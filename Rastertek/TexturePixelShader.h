#pragma once
#include "PixelShader.h"
#include "SamplerState.h"


class TexturePixelShader :
	public PixelShader
{
	SamplerState *samplerState{ nullptr };

public:
	TexturePixelShader(ID3D11Device *device);
	~TexturePixelShader();

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
};

