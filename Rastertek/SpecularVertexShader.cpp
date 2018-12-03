#include "SpecularVertexShader.h"



SpecularVertexShader::SpecularVertexShader(ID3D11Device *device)
	: matricesConstant(device), cameraConstant(device),
	VertexShader(device, "SpecularVertexShader.cso",
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		})
{
}


SpecularVertexShader::~SpecularVertexShader()
{
}

void SpecularVertexShader::Render(ID3D11DeviceContext * deviceContext)
{
	ID3D11Buffer* b[] = { matricesConstant(), cameraConstant() };
	deviceContext->VSSetConstantBuffers(0, ARRAYSIZE(b), b);
	VertexShader::Render(deviceContext);
}
