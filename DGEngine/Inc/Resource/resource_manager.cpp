#include "DGEngine_stdafx.h"
#include "resource_manager.h"

#include "mesh.h"
#include "texture.h"
#include "sampler.h"

using namespace DG;
using namespace DG::Math;

std::shared_ptr<Mesh> ResourceManager::mesh_nullptr_{};
std::shared_ptr<Texture> ResourceManager::texture_nullptr_{};
std::shared_ptr<Sampler> ResourceManager::sampler_nullptr_{};

void ResourceManager::Initialize()
{
	try
	{
		VertexColor color_triangle[3]{
			VertexColor{Vector3{0.f, 0.5f, 0.f}, DirectX::Colors::Red.v},
			VertexColor{Vector3{0.5f, -0.5f, 0.f}, DirectX::Colors::Green.v},
			VertexColor{Vector3{-0.5f, -0.5f, 0.f}, DirectX::Colors::Blue.v}
		};

		unsigned short indices[3]{ 0, 1, 2 };

		_CreateMesh(
			"ColorTri", "BasicShader", D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			color_triangle, sizeof(VertexColor), 3, D3D11_USAGE_DEFAULT,
			indices, 2, 3, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R16_UINT
		);
	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
	catch (...)
	{
		cerr << "ResourceManager::Initialize" << endl;
	}
}

shared_ptr<Mesh> const& ResourceManager::FindMesh(std::string const& _tag) const
{
	auto iter = mesh_map_.find(_tag);

	if (iter == mesh_map_.end())
		return mesh_nullptr_;

	return iter->second;
}

std::shared_ptr<Texture> const& ResourceManager::FindTexture(std::string const& _tag) const
{
	auto iter = texture_map_.find(_tag);

	if (iter == texture_map_.end())
		return texture_nullptr_;

	return iter->second;
}

std::shared_ptr<Sampler> const& ResourceManager::FindSampler(std::string const& _tag) const
{
	auto iter = sampler_map_.find(_tag);

	if (iter == sampler_map_.end())
		return sampler_nullptr_;

	return iter->second;
}

void ResourceManager::_Release()
{
}

void ResourceManager::_CreateMesh(
	string const& _tag, string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
	void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage,
	void* _idx_data, int _idx_size, int _idx_count, D3D11_USAGE _idx_usage, DXGI_FORMAT _idx_format)
{
	if (FindMesh(_tag))
		throw exception{ "ResourceManager::_CreateMesh" };

	auto mesh_buffer = shared_ptr<Mesh>{ new Mesh, [](Mesh* _p) {
		_p->_Release();
		delete _p;
	} };

	mesh_buffer->_CreateMesh(
		_tag, _vertex_shader_tag, _topology,
		_vtx_data, _vtx_size, _vtx_count, _vtx_usage,
		_idx_data, _idx_size, _idx_count, _idx_usage, _idx_format
	);

	mesh_map_.insert(make_pair(_tag, move(mesh_buffer)));
}

void ResourceManager::_CreateTexture2D(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag)
{
	if (FindTexture(_tag))
		throw std::exception{ "ResourceManager::_CreateTexture2D" };

	auto texture = std::shared_ptr<Texture>{ new Texture, [](Texture* _p) {
		_p->_Release();
		delete _p;
	} };

	texture->_LoadTexture2D(_tag, _file_name, _path_tag);

	texture_map_.insert(make_pair(_tag, std::move(texture)));
}

void ResourceManager::_CreateSampler(
	std::string const& _tag,
	D3D11_FILTER _filter,
	D3D11_TEXTURE_ADDRESS_MODE _address_u,
	D3D11_TEXTURE_ADDRESS_MODE _address_v,
	D3D11_TEXTURE_ADDRESS_MODE _address_w)
{
	if (FindSampler(_tag))
		throw std::exception{ "ResourceManager::_CreateSampler" };

	auto sampler = std::shared_ptr<Sampler>{ new Sampler, [](Sampler* _p) {
		_p->_Release();
		delete _p;
	} };

	sampler->_CreateSampler(_tag, _filter, _address_u, _address_v, _address_w);

	sampler_map_.insert(make_pair(_tag, std::move(sampler)));
}
