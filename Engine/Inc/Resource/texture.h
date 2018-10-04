#pragma once

#include "tag.h"

namespace DG
{
	class DG_ENGINE_DLL Texture final : public Tag
	{
		friend class ResourceManager;
	protected:
		Texture() = default;
		Texture(Texture const& _other);
		Texture(Texture&& _other) noexcept;
		Texture& operator=(Texture const&) = default;
		Texture& operator=(Texture&&) noexcept = default;

		virtual void _Release() override;

		void _LoadTexture2D(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag);
		void _SetShaderResourceView(int _slot);

		std::vector<Microsoft::WRL::ComPtr<ID3D11Texture2D>> texture_2d_vector_{};
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV_{};
	};
}
