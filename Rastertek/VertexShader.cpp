#include "VertexShader.h"



VertexShader::VertexShader(ID3D11Device *device, std::string filename, std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements)
{
	auto bytecode = LoadFile(filename);
	HRESULT hr = S_OK;
	if (FAILED(hr = device->CreateVertexShader(bytecode.data(), bytecode.size(), nullptr, &shader)))
		throw std::exception("Cannot to create a vertex shader.");

	if (FAILED(device->CreateInputLayout(inputElements.data(), inputElements.size(), bytecode.data(), bytecode.size(), &inputLayout)))
		throw std::exception("Cannot to create an input layout.");	
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
