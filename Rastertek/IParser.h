#pragma once

#include <vector>


__interface IParser
{

};

template <typename TOutput>
__interface IConcreteParser : public IParser
{
	std::vector<TOutput> Load(std::wstring filename);
};