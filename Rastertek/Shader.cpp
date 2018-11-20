#include "Shader.h"
#include <fstream>


std::vector<char> Shader::LoadFile(std::string filename)
{
	std::ifstream file{ filename };
	if (file.bad() || !file.good())
		throw std::exception(("File: " + filename + " is not found.").c_str());

	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);

	file.read(buffer.data(), size);

	return std::move(buffer);
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
