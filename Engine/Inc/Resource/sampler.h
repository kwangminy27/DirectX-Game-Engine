#pragma once

#include "tag.h"

namespace DG
{
	class DG_ENGINE_DLL Sampler final : public Tag
	{
		friend class ResourceManager;
	public:
		void SetToShader(int _slot);

	private:
		Sampler() = default;
		Sampler(Sampler const& _other);
		Sampler(Sampler&& _other) noexcept;
		Sampler& operator=(Sampler const&) = default;
		Sampler& operator=(Sampler&&) noexcept = default;

		virtual void _Release() override;

		void _CreateSampler(
			std::string const& _tag,
			D3D11_FILTER _filter,
			D3D11_TEXTURE_ADDRESS_MODE _address_u,
			D3D11_TEXTURE_ADDRESS_MODE _address_v,
			D3D11_TEXTURE_ADDRESS_MODE _address_w);

		Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_{};
	};
}
