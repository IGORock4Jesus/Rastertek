#pragma once

#include <D3D11.h>


class SamplerState
{
	ID3D11SamplerState *state{ nullptr };

public:
	SamplerState(ID3D11Device *device);
	~SamplerState();

	ID3D11SamplerState *Get() { return state; }
};

