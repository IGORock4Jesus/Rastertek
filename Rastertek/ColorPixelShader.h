#pragma once
#include "PixelShader.h"


class ColorPixelShader : public PixelShader
{
public:
	ColorPixelShader(ID3D11Device *device);
	~ColorPixelShader();
};

