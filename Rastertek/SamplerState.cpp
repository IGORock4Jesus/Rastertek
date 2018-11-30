#include "SamplerState.h"
#include <exception>


SamplerState::SamplerState(ID3D11Device *device)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = desc.AddressV = desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	if (FAILED(device->CreateSamplerState(&desc, &state)))
		throw std::exception("Cannot to create a sampler state.");
}


SamplerState::~SamplerState()
{
	if (state)
		state->Release();
}
