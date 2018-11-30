#include "TexturePixelShader.h"



TexturePixelShader::TexturePixelShader(ID3D11Device *device)
	: PixelShader(device, "TexturePixelShader.cso")
{
}


TexturePixelShader::~TexturePixelShader()
{
}

void TexturePixelShader::Render(ID3D11DeviceContext * deviceContext)
{
	ID3D11SamplerState *ss[]{ samplerState->Get() };
	deviceContext->PSSetSamplers(0, 1, ss);
}
