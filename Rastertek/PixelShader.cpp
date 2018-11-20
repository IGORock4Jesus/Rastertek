#include "PixelShader.h"



PixelShader::PixelShader(ID3D11Device *device, std::string filename)
{
	auto bytecode = LoadFile(filename);
	device->CreatePixelShader(bytecode.data(), bytecode.size(), nullptr, &shader);
}


PixelShader::~PixelShader()
{
	if (shader)
		shader->Release();
}

void PixelShader::Render(ID3D11DeviceContext * deviceContext)
{
	deviceContext->PSSetShader(shader, nullptr, 0);
}
