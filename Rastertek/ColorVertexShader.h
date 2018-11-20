#pragma once

#include "VertexShader.h"
#include <D3DX10.h>
#include "ConstantBuffer.h"


class ColorVertexShader : public VertexShader
{
	struct Matrices
	{
		D3DXMATRIX world, view, proj;
	};
	ConstantBuffer<Matrices> matricesConstant;

public:
	ColorVertexShader(ID3D11Device *device);
	~ColorVertexShader();

	ConstantBuffer<Matrices>& GetMatricesConstantBuffer() { return matricesConstant; }
};

