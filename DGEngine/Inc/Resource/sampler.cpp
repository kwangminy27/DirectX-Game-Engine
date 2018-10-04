#include "DGEngine_stdafx.h"
#include "sampler.h"

#include "device.h"

using namespace DG;

void Sampler::SetToShader(int _slot)
{
	Device::singleton()->context()->PSSetSamplers(_slot, 1, sampler_.GetAddressOf());
}

Sampler::Sampler(Sampler const& _other) : Tag(_other)
{
	sampler_ = _other.sampler_;
}

Sampler::Sampler(Sampler&& _other) noexcept : Tag(std::move(_other))
{
	sampler_ = std::move(_other.sampler_);
}

void Sampler::_Release()
{
}

void Sampler::_CreateSampler(
	std::string const& _tag,
	D3D11_FILTER _filter,
	D3D11_TEXTURE_ADDRESS_MODE _address_u,
	D3D11_TEXTURE_ADDRESS_MODE _address_v,
	D3D11_TEXTURE_ADDRESS_MODE _address_w)
{
	tag_ = _tag;

	auto const& device = Device::singleton()->device();

	D3D11_SAMPLER_DESC sampler_desc{};
	sampler_desc.Filter = _filter;
	sampler_desc.AddressU = _address_u;
	sampler_desc.AddressV = _address_v;
	sampler_desc.AddressW = _address_w;
	sampler_desc.MaxAnisotropy = 1;

	ThrowIfFailed(device->CreateSamplerState(&sampler_desc, &sampler_));
}
