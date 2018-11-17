#pragma once

#include "singleton.h"

namespace DG
{
	class Mesh;
	class Texture;
	class Sampler;

	class DG_ENGINE_DLL ResourceManager final : public Singleton<ResourceManager>
	{
		friend class Singleton<ResourceManager>;
	public:
		void Initialize();
		std::shared_ptr<Mesh> const& FindMesh(std::string const& _tag) const;
		std::shared_ptr<Texture> const& FindTexture(std::string const& _tag) const;
		std::shared_ptr<Sampler> const& FindSampler(std::string const& _tag) const;
		std::shared_ptr<Animation2DClipDesc> const& FindAnimation2DClip(std::string const& _tag) const;

	private:
		ResourceManager() = default;
		ResourceManager(ResourceManager const&) = delete;
		ResourceManager(ResourceManager&&) noexcept = delete;
		ResourceManager& operator=(ResourceManager const&) = delete;
		ResourceManager& operator=(ResourceManager&&) noexcept = delete;

		virtual void _Release() override;

		void _CreateMesh(
			std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
			void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
			void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format,
			void* _inst_data, int _inst_size, int _inst_count, D3D11_USAGE _inst_usage);
		void _CreateMesh(
			std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
			void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
			void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format);
		void _CreateMesh(
			std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
			void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage);
		void _CreateTexture2D(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag);
		void _CreateSampler(
			std::string const& _tag,
			D3D11_FILTER _filter,
			D3D11_TEXTURE_ADDRESS_MODE _address_u,
			D3D11_TEXTURE_ADDRESS_MODE _address_v,
			D3D11_TEXTURE_ADDRESS_MODE _address_w);
		void _LoadAnimation2DClip(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag);

		static std::shared_ptr<Mesh> mesh_nullptr_;
		static std::shared_ptr<Texture> texture_nullptr_;
		static std::shared_ptr<Sampler> sampler_nullptr_;
		static std::shared_ptr<Animation2DClipDesc> animation_2d_clip_nullptr_;
		std::unordered_map<std::string, std::shared_ptr<Mesh>> mesh_map_{};
		std::unordered_map<std::string, std::shared_ptr<Texture>> texture_map_{};
		std::unordered_map<std::string, std::shared_ptr<Sampler>> sampler_map_{};
		std::unordered_map<std::string, std::shared_ptr<Animation2DClipDesc>> animation_2d_clip_map_{};
	};
}