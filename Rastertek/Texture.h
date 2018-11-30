#pragma once

#include <D3D11.h>
#include <string>


class Texture
{
	ID3D11ShaderResourceView *view{ nullptr };

public:
	Texture(ID3D11Device *device, std::wstring filename);
	~Texture();

	ID3D11ShaderResourceView *Get() { return view; }
};

