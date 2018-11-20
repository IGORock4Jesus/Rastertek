#include "ColorPixelShader.h"



ColorPixelShader::ColorPixelShader(ID3D11Device *device)
	: PixelShader(device, "ColorPixelShader.cso")
{
}


ColorPixelShader::~ColorPixelShader()
{
}
