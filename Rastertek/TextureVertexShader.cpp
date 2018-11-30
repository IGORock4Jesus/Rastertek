#include "TextureVertexShader.h"



TextureVertexShader::TextureVertexShader(ID3D11Device *device)
	: matricesConstant(device), VertexShader(device, "TextureVertexShader.cso",
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		})
{
}


TextureVertexShader::~TextureVertexShader()
{
}

void TextureVertexShader::Render(ID3D11DeviceContext * deviceContext)
{
	ID3D11Buffer* b[] = { matricesConstant() };
	deviceContext->VSSetConstantBuffers(0, 1, b);
	VertexShader::Render(deviceContext);
}
