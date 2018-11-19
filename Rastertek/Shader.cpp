#include "Shader.h"
#include <fstream>


std::vector<char> Shader::LoadFile(std::wstring filename)
{
	std::ifstream file{ filename };
	if (file.bad() || !file.good())
		throw std::exception((L"File: " + filename + L" is not found.").c_str());


	return std::vector<char>();
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
