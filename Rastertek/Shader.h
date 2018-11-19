#pragma once

#include <vector>


class Shader
{
protected:
	std::vector<char> LoadFile(std::wstring filename);

public:
	Shader();
	virtual ~Shader();
};

