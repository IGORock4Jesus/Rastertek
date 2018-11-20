#include "VertexShader.h"



VertexShader::VertexShader(ID3D11Device *device, std::string filename, std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements)
{
	auto bytecode = LoadFile(filename);
	device->CreateVertexShader(bytecode.data(), bytecode.size(), nullptr, &shader);

	device->CreateInputLayout(inputElements.data(), inputElements.size(), bytecode.data(), bytecode.size(), &inputLayout);

}


VertexShader::~VertexShader()
{
	if (shader)
		shader->Release();
	if (inputLayout)
		inputLayout->Release();
}

void VertexShader::Render(ID3D11DeviceContext * deviceContext)
{
	deviceContext->VSSetShader(shader, nullptr, 0);
	deviceContext->IASetInputLayout(inputLayout);
}
