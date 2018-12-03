#pragma once
#include "VertexShader.h"
#include "ConstantBuffer.h"
#include <D3DX10.h>


class SpecularVertexShader :
	public VertexShader
{
	struct Matrices
	{
		D3DXMATRIX world, view, proj;
	};

	struct CameraBuffer
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	ConstantBuffer<Matrices> matricesConstant;
	ConstantBuffer<CameraBuffer> cameraConstant;

public:
	SpecularVertexShader(ID3D11Device *device);
	~SpecularVertexShader();

	ConstantBuffer<Matrices>& GetMatricesConstantBuffer() { return matricesConstant; }
	ConstantBuffer<CameraBuffer>& GetCameraConstantBuffer() { return cameraConstant; }

	virtual void Render(ID3D11DeviceContext *deviceContext) override;
};

