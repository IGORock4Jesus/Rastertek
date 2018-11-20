#pragma once

#include <vector>
#include <D3D11.h>


class Shader
{
protected:
	std::vector<char> LoadFile(std::string filename);

public:
	Shader();
	virtual ~Shader();

	virtual void Render(ID3D11DeviceContext *deviceContext) = 0;
};

