#pragma once
#include "VertexShader.h"
#include "ConstantBuffer.h"
#include <D3DX10.h>


class DiffuseVertexShader :
	public VertexShader
{
	struct Matrices
	{
		D3DXMATRIX world, view, proj;
	};
	ConstantBuffer<Matrices> matricesConstant;

public:
	DiffuseVertexShader(ID3D11Device *device);
	~DiffuseVertexShader();

	ConstantBuffer<Matrices>& GetMatricesConstantBuffer() { return matricesConstant; }

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
};

