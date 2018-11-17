
#include "DGEngine_stdafx.h"
#include "mesh.h"

#include "device.h"

using namespace DG;

void Mesh::Render()
{
	auto const& context = Device::singleton()->context();

	for (auto const& _mesh_container : mesh_container_vector_)
	{
		context->IASetPrimitiveTopology(_mesh_container->topology);

		std::vector<UINT> stride{};
		std::vector<UINT> offset{};
		std::vector<ID3D11Buffer*> buffer{};

		for (auto const& _VB : _mesh_container->VB_vector)
		{
			stride.push_back(_VB.size);
			offset.push_back(0);
			buffer.push_back(_VB.buffer.Get());
		}

		context->IASetVertexBuffers(0, static_cast<UINT>(_mesh_container->VB_vector.size()), buffer.data(), stride.data(), offset.data());

		if (_mesh_container->IB_vector.empty())
		{
			if (_mesh_container->VB_vector.size() == 1)
				context->Draw(_mesh_container->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::VERTEX)).count, 0);
			else
				context->DrawInstanced(_mesh_container->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::VERTEX)).count, _mesh_container->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::INSTANCE)).count, 0, 0);
		}
		else
		{
			if (_mesh_container->VB_vector.size() == 1)
			{
				for (auto const& IB : _mesh_container->IB_vector)
				{
					context->IASetIndexBuffer(IB.buffer.Get(), IB.format, 0);
					context->DrawIndexed(IB.count, 0, 0);
				}
			}
			else
			{
				for (auto const& IB : _mesh_container->IB_vector)
				{
					context->IASetIndexBuffer(IB.buffer.Get(), IB.format, 0);
					context->DrawIndexedInstanced(IB.count, _mesh_container->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::INSTANCE)).count, 0, 0, 0);
				}
			}
		}
	}
}

void Mesh::Render(int _container_idx, int _subset_idx)
{
	auto const& context = Device::singleton()->context();
	auto const& mesh_container = mesh_container_vector_.at(_container_idx);

	context->IASetPrimitiveTopology(mesh_container->topology);

	std::vector<UINT> stride{};
	std::vector<UINT> offset{};
	std::vector<ID3D11Buffer*> buffer{};

	for (auto const& _VB : mesh_container->VB_vector)
	{
		stride.push_back(_VB.size);
		offset.push_back(0);
		buffer.push_back(_VB.buffer.Get());
	}

	context->IASetVertexBuffers(0, static_cast<UINT>(mesh_container->VB_vector.size()), buffer.data(), stride.data(), offset.data());

	auto const& IB = mesh_container->IB_vector.at(_subset_idx);
	if (mesh_container->VB_vector.size() == 1)
	{
		context->IASetIndexBuffer(IB.buffer.Get(), IB.format, 0);
		context->DrawIndexed(IB.count, 0, 0);
	}
	else
	{
		context->IASetIndexBuffer(IB.buffer.Get(), IB.format, 0);
		context->DrawIndexedInstanced(IB.count, mesh_container->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::INSTANCE)).count, 0, 0, 0);
	}
}

size_t Mesh::GetContainerSize() const
{
	return mesh_container_vector_.size();
}

size_t Mesh::GetSubsetSize(int _container_idx) const
{
	return mesh_container_vector_.at(_container_idx)->IB_vector.size();
}

Microsoft::WRL::ComPtr<ID3D11Buffer> Mesh::GetInstanceBuffer(int _container_idx, int _subset_idx)
{
	return mesh_container_vector_.at(_container_idx)->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::INSTANCE)).buffer;
}

void Mesh::SetInstanceCount(int _count, int _container_idx, int _subset_idx)
{
	mesh_container_vector_.at(_container_idx)->VB_vector.at(static_cast<int>(VERTEX_BUFFER_TYPE::INSTANCE)).count = _count;
}

Math::Vector3 const& Mesh::center() const
{
	return center_;
}

Math::Vector3 const& Mesh::min() const
{
	return min_;
}

Math::Vector3 const& Mesh::max() const
{
	return max_;
}

Math::Vector3 const& Mesh::diagonal() const
{
	return diagonal_;
}

float Mesh::radius() const
{
	return radius_;
}

Mesh::Mesh(Mesh const& _other) : Tag(_other)
{
	mesh_container_vector_ = _other.mesh_container_vector_;
	center_ = _other.center_;
	radius_ = _other.radius_;
	min_ = _other.min_;
	max_ = _other.max_;
	diagonal_ = _other.diagonal_;
}

Mesh::Mesh(Mesh&& _other) noexcept : Tag(std::move(_other))
{
	mesh_container_vector_ = std::move(_other.mesh_container_vector_);
	center_ = std::move(_other.center_);
	radius_ = std::move(_other.radius_);
	min_ = std::move(_other.min_);
	max_ = std::move(_other.max_);
	diagonal_ = std::move(_other.diagonal_);
}

void Mesh::_Release()
{
}

void Mesh::_CreateMesh(
	std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
	void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
	void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format,
	void* _inst_data, int _inst_size, int _inst_count, D3D11_USAGE _inst_usage)
{
	set_tag(_tag);

	auto mesh_container_buffer = std::shared_ptr<MeshContainer>{ new MeshContainer, [](MeshContainer* _p) {
		for (auto& VB : _p->VB_vector)
			delete[] VB.data;
		for (auto& IB : _p->IB_vector)
			delete[] IB.data;
		delete _p;
	} };
	mesh_container_buffer->topology = _topology;

	mesh_container_vector_.push_back(move(mesh_container_buffer));
	mesh_container_vector_.at(mesh_container_vector_.size() - 1)->VB_vector.resize(2);

	_CreateVertexBuffer(_vtx_data, _vtx_size, _vtx_count, _vtx_usage, VERTEX_BUFFER_TYPE::VERTEX);
	_CreateVertexBuffer(_inst_data, _inst_size, _inst_count, _inst_usage, VERTEX_BUFFER_TYPE::INSTANCE);
	_CreateIndexBuffer(_idx_data, _idx_size, _idx_count, _idx_usage, _idx_format);
}

void Mesh::_CreateMesh(
	std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
	void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
	void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format)
{
	set_tag(_tag);

	auto mesh_container_buffer = std::shared_ptr<MeshContainer>{ new MeshContainer, [](MeshContainer* _p) {
		for (auto& VB : _p->VB_vector)
			delete[] VB.data;
		for (auto& IB : _p->IB_vector)
			delete[] IB.data;
		delete _p;
	} };
	mesh_container_buffer->topology = _topology;

	mesh_container_vector_.push_back(move(mesh_container_buffer));
	mesh_container_vector_.at(mesh_container_vector_.size() - 1)->VB_vector.resize(1);

	_CreateVertexBuffer(_vtx_data, _vtx_size, _vtx_count, _vtx_usage, VERTEX_BUFFER_TYPE::VERTEX);
	_CreateIndexBuffer(_idx_data, _idx_size, _idx_count, _idx_usage, _idx_format);
}

void Mesh::_CreateMesh(
	std::string const& _tag, std::string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
	void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage)
{
	set_tag(_tag);

	auto mesh_container_buffer = std::shared_ptr<MeshContainer>{ new MeshContainer, [](MeshContainer* _p) {
		for (auto& VB : _p->VB_vector)
			delete[] VB.data;
		for (auto& IB : _p->IB_vector)
			delete[] IB.data;
		delete _p;
	} };
	mesh_container_buffer->topology = _topology;

	mesh_container_vector_.push_back(move(mesh_container_buffer));
	mesh_container_vector_.at(mesh_container_vector_.size() - 1)->VB_vector.resize(1);

	_CreateVertexBuffer(_vtx_data, _vtx_size, _vtx_count, _vtx_usage, VERTEX_BUFFER_TYPE::VERTEX);
}

void Mesh::_CreateVertexBuffer(void* _data, int _size, int _count, D3D11_USAGE _usage, VERTEX_BUFFER_TYPE _type)
{
	auto const& device = Device::singleton()->device();

	auto& mesh_container = mesh_container_vector_.at(mesh_container_vector_.size() - 1);
	mesh_container->VB_vector.at(static_cast<int>(_type)).size = _size;
	mesh_container->VB_vector.at(static_cast<int>(_type)).count = _count;
	mesh_container->VB_vector.at(static_cast<int>(_type)).usage = _usage;

	int byte_width = _size * _count;
	mesh_container->VB_vector.at(static_cast<int>(_type)).data = new char[byte_width];
	memcpy_s(mesh_container->VB_vector.at(static_cast<int>(_type)).data, byte_width, _data, byte_width);

	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.ByteWidth = byte_width;
	buffer_desc.Usage = _usage;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (_usage == D3D11_USAGE_DYNAMIC)
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subresource_data{};
	subresource_data.pSysMem = mesh_container->VB_vector.at(static_cast<int>(_type)).data;

	ThrowIfFailed(device->CreateBuffer(&buffer_desc, &subresource_data, &mesh_container->VB_vector.at(static_cast<int>(_type)).buffer));

	if (_type == VERTEX_BUFFER_TYPE::INSTANCE)
		return;

	char* vertices = static_cast<char*>(_data);

	Math::Vector3 position{};
	int position_size = sizeof(Math::Vector3);

	memcpy_s(&position, position_size, vertices, position_size);
	min_ = position;
	max_ = position;

	for (int i = 0; i < _count; ++i)
	{
		memcpy_s(&position, position_size, vertices + _size * i, position_size);

		if (min_.x > position.x)
			min_.x = position.x;
		if (min_.y > position.y)
			min_.y = position.y;
		if (min_.z > position.z)
			min_.z = position.z;

		if (max_.x < position.x)
			max_.x = position.x;
		if (max_.y < position.y)
			max_.y = position.y;
		if (max_.z < position.z)
			max_.z = position.z;
	}

	center_ = (min_ + max_) / 2.f;
	diagonal_ = max_ - min_;
	radius_ = diagonal_.Length() / 2.f;
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
