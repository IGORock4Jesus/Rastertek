#include "Shader.h"
#include <fstream>


std::vector<char> Shader::LoadFile(std::string filename)
{
	std::vector<char> data;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.bad() || !file.good())
		throw std::exception(("File: " + filename + " is not found.").c_str());
	data.resize(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&data[0], data.size());
	return std::move(data);
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
