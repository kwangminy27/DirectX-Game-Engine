#include "DGEngine_stdafx.h"
#include "resource_manager.h"

#include "mesh.h"

using namespace std;
using namespace DG;
using namespace DG::Math;

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

shared_ptr<Mesh> const& ResourceManager::FindMesh(string const& _tag)
{
	auto iter = mesh_map_.find(_tag);

	if (iter == mesh_map_.end())
		return mesh_nullptr_;

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
