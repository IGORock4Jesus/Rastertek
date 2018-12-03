#include "SimpleParser.h"


std::vector<Vertex> SimpleParser::Load(std::wstring filename)
{
	std::ifstream file{ filename };
	if (file.bad() || !file.good())
		return {};

	size_t size;
	file >> size;

	std::vector<Vertex> o{ size };

	for (size_t i = 0; i < size; i++)
	{
		file >> o[i].position.x >> o[i].position.y >> o[i].position.z 
			 >> o[i].texel.x >> o[i].texel.y
			 >> o[i].normal.x >> o[i].normal.y >> o[i].normal.z;
	}

	return std::move(o);
}
