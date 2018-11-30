#include "Texture.h"
#include <D3DX11tex.h>



Texture::Texture(ID3D11Device * device, std::wstring filename)
{
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(device, filename.c_str(), nullptr, nullptr, &view, nullptr)))
		throw std::exception("Cannot to load a texture from file.");
}

Texture::~Texture()
{
	if (view)
		view->Release();
}
