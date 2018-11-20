#pragma once

#include "Shader.h"
#include <D3D11.h>


class PixelShader :
	public Shader
{
	ID3D11PixelShader *shader{ nullptr };

public:
	PixelShader(ID3D11Device *device, std::string filename);
	virtual ~PixelShader();

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
};

