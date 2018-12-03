#include "SpecularPixelShader.h"



SpecularPixelShader::SpecularPixelShader(ID3D11Device *device)
	: PixelShader(device, "SpecularPixelShader.cso"),
	constantBuffer{ device }
{
	samplerState = new SamplerState(device);
}


SpecularPixelShader::~SpecularPixelShader()
{
	delete samplerState;
}

void SpecularPixelShader::Render(ID3D11DeviceContext * deviceContext)
{
	ID3D11SamplerState *ss[]{ samplerState->Get() };
	deviceContext->PSSetSamplers(0, 1, ss);

	ID3D11Buffer *conbs[]{ constantBuffer() };
	deviceContext->PSSetConstantBuffers(0, 1, conbs);

	PixelShader::Render(deviceContext);
}
