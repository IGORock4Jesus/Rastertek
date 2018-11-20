#pragma once
#include "Shader.h"
#include <D3D11.h>

class VertexShader : public Shader
{
	ID3D11VertexShader *shader{ nullptr };
	ID3D11InputLayout *inputLayout{ nullptr };

public:
	VertexShader(ID3D11Device *device, std::string filename, std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements);
	virtual ~VertexShader();

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
};

