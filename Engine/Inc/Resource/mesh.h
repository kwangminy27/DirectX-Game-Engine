#pragma once

#include "tag.h"

namespace DG
{
	struct DG_ENGINE_DLL VertexBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		void* data;
		int size;
		int count;
		D3D11_USAGE usage;
	};

	struct DG_ENGINE_DLL IndexBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		void* data;
		int size;
		int count;
		D3D11_USAGE usage;
		DXGI_FORMAT format;
	};

	struct DG_ENGINE_DLL MeshContainer
	{
		D3D11_PRIMITIVE_TOPOLOGY topology;
		VertexBuffer VB;
		std::vector<IndexBuffer> IB_vector;
	};

	class DG_ENGINE_DLL Mesh final : public Tag
	{
		friend class ResourceManager;
	public:
		void Render();

	private:
		Mesh() = default;
		Mesh(Mesh const& _other);
		Mesh(Mesh&& _other) noexcept;
		Mesh& operator=(Mesh const&) = default;
		Mesh& operator=(Mesh&&) noexcept = default;

		virtual void _Release() override;

		void _CreateMesh(
			std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
			void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
			void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format);
		void _CreateVertexBuffer(void* _data, int _size, int _count, D3D11_USAGE _usage);
		void _CreateIndexBuffer(void* _data, int _size, int _count, D3D11_USAGE _usage, DXGI_FORMAT _format);
		void _UpdateVertexBuffer(void* _data, int _mesh_container_idx);

		std::vector<std::shared_ptr<MeshContainer>> mesh_container_vector_{};
	};
}
