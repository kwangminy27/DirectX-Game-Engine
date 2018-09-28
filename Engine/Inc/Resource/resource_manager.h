#pragma once

#include "singleton.h"

namespace DG
{
	class Mesh;

	class DG_ENGINE_DLL ResourceManager final : public Singleton<ResourceManager>
	{
		friend class Singleton<ResourceManager>;
	public:
		void Initialize();
		std::shared_ptr<Mesh> const& FindMesh(string const& _tag) const;

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
			void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format);

		std::shared_ptr<Mesh> mesh_nullptr_{};
		std::unordered_map<std::string, std::shared_ptr<Mesh>> mesh_map_{};
	};
}