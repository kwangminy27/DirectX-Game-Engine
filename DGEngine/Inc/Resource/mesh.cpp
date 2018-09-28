
#include "DGEngine_stdafx.h"
#include "mesh.h"

#include "device.h"

using namespace std;
using namespace DG;

void Mesh::Render()
{
	auto const& context = Device::singleton()->context();

	for (auto const& mesh_container : mesh_container_vector_)
	{
		context->IASetPrimitiveTopology(mesh_container->topology);

		UINT stride{ static_cast<UINT>(mesh_container->VB.size) };
		UINT offset{};
		context->IASetVertexBuffers(0, 1, mesh_container->VB.buffer.GetAddressOf(), &stride, &offset);

		if (mesh_container->IB_vector.empty())
			context->Draw(mesh_container->VB.count, 0);
		else
		{
			for (auto const& IB : mesh_container->IB_vector)
			{
				context->IASetIndexBuffer(IB.buffer.Get(), IB.format, 0);
				context->DrawIndexed(IB.count, 0, 0);
			}
		}
	}
}

Mesh::Mesh(Mesh const& _other) : Tag(_other)
{
	mesh_container_vector_ = _other.mesh_container_vector_;
}

Mesh::Mesh(Mesh&& _other) noexcept : Tag(move(_other))
{
	mesh_container_vector_ = move(_other.mesh_container_vector_);
}

void Mesh::_Release()
{
}

void Mesh::_CreateMesh(
	string const& _tag, string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
	void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
	void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format)
{
	set_tag(_tag);

	auto mesh_container_buffer = shared_ptr<MeshContainer>{ new MeshContainer, [](MeshContainer* _p) {
		delete[] _p->VB.data;
		for (auto& IB : _p->IB_vector)
			delete[] IB.data;
		delete _p;
	} };
	mesh_container_buffer->topology = _topology;

	mesh_container_vector_.push_back(move(mesh_container_buffer));

	_CreateVertexBuffer(_vtx_data, _vtx_size, _vtx_count, _vtx_usage);
	_CreateIndexBuffer(_idx_data, _idx_size, _idx_count, _idx_usage, _idx_format);
}

void Mesh::_CreateVertexBuffer(void* _data, int _size, int _count, D3D11_USAGE _usage)
{
	auto& mesh_container = mesh_container_vector_.at(mesh_container_vector_.size() - 1);
	mesh_container->VB.size = _size;
	mesh_container->VB.count = _count;
	mesh_container->VB.usage = _usage;

	int byte_width = _size * _count;
	mesh_container->VB.data = new char[byte_width];
	memcpy_s(mesh_container->VB.data, byte_width, _data, byte_width);

	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.ByteWidth = byte_width;
	buffer_desc.Usage = _usage;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (_usage == D3D11_USAGE_DYNAMIC)
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subresource_data{};
	subresource_data.pSysMem = mesh_container->VB.data;

	ThrowIfFailed(Device::singleton()->device()->CreateBuffer(&buffer_desc, &subresource_data, &mesh_container->VB.buffer));
}

void Mesh::_CreateIndexBuffer(void* _data, int _size, int _count, D3D11_USAGE _usage, DXGI_FORMAT _format)
{
	auto& mesh_container = mesh_container_vector_.at(mesh_container_vector_.size() - 1);

	IndexBuffer IB{};
	IB.size = _size;
	IB.count = _count;
	IB.usage = _usage;
	IB.format = _format;

	int byte_width = _size * _count;
	IB.data = new char[byte_width];
	memcpy_s(IB.data, byte_width, _data, byte_width);

	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.ByteWidth = byte_width;
	buffer_desc.Usage = _usage;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	if (_usage == D3D11_USAGE_DYNAMIC)
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subresource_data{};
	subresource_data.pSysMem = IB.data;

	ThrowIfFailed(Device::singleton()->device()->CreateBuffer(&buffer_desc, &subresource_data, &IB.buffer));

	mesh_container->IB_vector.push_back(move(IB));
}

void Mesh::_UpdateVertexBuffer(void* _data, int _mesh_container_idx)
{
	if (_mesh_container_idx < 0 || _mesh_container_idx >= mesh_container_vector_.size())
		throw exception{ "Mesh::_UpdateVertexBuffer" };

	auto& mesh_container = mesh_container_vector_.at(_mesh_container_idx);

	int byte_width = mesh_container->VB.size * mesh_container->VB.count;
	memcpy_s(mesh_container->VB.data, byte_width, _data, byte_width);

	switch (mesh_container->VB.usage)
	{
	case D3D11_USAGE_DEFAULT:
		Device::singleton()->context()->UpdateSubresource(mesh_container->VB.buffer.Get(), 0, nullptr, _data, 0, 0);
		break;

	case D3D11_USAGE_DYNAMIC:
		D3D11_MAPPED_SUBRESOURCE mapped_subresource{};
		Device::singleton()->context()->Map(mesh_container->VB.buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
		memcpy_s(mapped_subresource.pData, byte_width, _data, byte_width);
		Device::singleton()->context()->Unmap(mesh_container->VB.buffer.Get(), 0);
		break;
	}
}
