#include "DiffusePixelShader.h"



DiffusePixelShader::DiffusePixelShader(ID3D11Device *device)
	: PixelShader(device, "DiffusePixelShader.cso"),
	constantBuffer{ device }
{
	samplerState = new SamplerState(device);
}


DiffusePixelShader::~DiffusePixelShader()
{
	delete samplerState;
}

void DiffusePixelShader::Render(ID3D11DeviceContext * deviceContext)
{
	ID3D11SamplerState *ss[]{ samplerState->Get() };
	deviceContext->PSSetSamplers(0, 1, ss);

	ID3D11Buffer *conbs[]{ constantBuffer() };
	deviceContext->PSSetConstantBuffers(0, 1, conbs);

	PixelShader::Render(deviceContext);
}
