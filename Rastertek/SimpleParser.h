#pragma once

#include <fstream>
#include <vector>
#include "IParser.h"
#include "Vertex.h"


class SimpleParser : public IConcreteParser<Vertex> {
public:


public:
	virtual std::vector<Vertex> Load(std::wstring filename) override;

};

