#pragma once

#include "IParser.h"
#include "Vertex.h"


class ObjParser : public IConcreteParser<Vertex>
{
public:
	ObjParser();
	~ObjParser();

	// ������������ ����� IConcreteParser
	virtual std::vector<Vertex> Load(std::wstring filename) override;
};

