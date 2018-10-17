#include "DGEngine_stdafx.h"
#include "resource_manager.h"

#include "path_manager.h"
#include "mesh.h"
#include "texture.h"
#include "sampler.h"

using namespace filesystem;
using namespace DG;

std::shared_ptr<Mesh> ResourceManager::mesh_nullptr_{};
std::shared_ptr<Texture> ResourceManager::texture_nullptr_{};
std::shared_ptr<Sampler> ResourceManager::sampler_nullptr_{};
std::shared_ptr<Animation2DClipDesc> ResourceManager::animation_2d_clip_nullptr_{};

void ResourceManager::Initialize()
{
	try
	{
		// ColorTri
		VertexColor color_triangle[3]{
			VertexColor{ Math::Vector3{ 50.f, 100.f, 0.f } , DirectX::Colors::Red.v },
			VertexColor{ Math::Vector3{ 100.f, 0.f, 0.f }, DirectX::Colors::Green.v },
			VertexColor{ Math::Vector3{ 0.f, 0.f, 0.f }, DirectX::Colors::Blue.v }
		};

		unsigned short color_triagle_indices[3]{ 0, 1, 2 };

		_CreateMesh(
			"ColorTri", BASIC_SHADER, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			color_triangle, sizeof(VertexColor), 3, D3D11_USAGE_DEFAULT,
			color_triagle_indices, 2, 3, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R16_UINT
		);

		// TexRect
		VertexTex tex_rect[4]{
			VertexTex{ Math::Vector3{ 0.f, 0.f, 0.f }, Math::Vector2{ 0.f, 1.f } },
			VertexTex{ Math::Vector3{ 0.f, 100.f, 0.f }, Math::Vector2{ 0.f, 0.f } },
			VertexTex{ Math::Vector3{ 100.f, 0.f, 0.f }, Math::Vector2{ 1.f, 1.f } },
			VertexTex{ Math::Vector3{ 100.f, 100.f, 0.f }, Math::Vector2{ 1.f, 0.f } },
		};

		unsigned short tex_rect_indices[6]{ 0, 1, 2, 1, 3, 2 };

		_CreateMesh(
			"TexRect", BASIC_TEX_SHADER, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			tex_rect, sizeof(VertexTex), 4, D3D11_USAGE_DEFAULT,
			tex_rect_indices, 2, 6, D3D11_USAGE_DEFAULT, DXGI_FORMAT_R16_UINT
		);

#ifdef _DEBUG
		// ColliderRect
		Math::Vector3 collider_rect[5]{
			Math::Vector3{ 0.f, 100.f, 0.f },
			Math::Vector3{ 100.f, 100.f, 0.f },
			Math::Vector3{ 100.f, 0.f, 0.f },
			Math::Vector3{ 0.f, 0.f, 0.f },
			Math::Vector3{ 0.f, 100.f, 0.f }
		};

		_CreateMesh(
			"ColliderRect", COLLIDER_SHADER, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
			collider_rect, sizeof(Math::Vector3), 5, D3D11_USAGE_DEFAULT
		);
#endif

		_CreateTexture2D("Player", L"Player.png", TEXTURE_PATH);
		_CreateSampler(
			LINEAR_SAMPLER,
			D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			D3D11_TEXTURE_ADDRESS_CLAMP,
			D3D11_TEXTURE_ADDRESS_CLAMP,
			D3D11_TEXTURE_ADDRESS_CLAMP
		);

		_LoadAnimation2DClip("Player", L"animation_2d.csv", DATA_PATH);
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

std::shared_ptr<Animation2DClipDesc> const& ResourceManager::FindAnimation2DClip(std::string const& _tag) const
{
	auto iter = animation_2d_clip_map_.find(_tag);

	if (iter == animation_2d_clip_map_.end())
		return animation_2d_clip_nullptr_;

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

void ResourceManager::_CreateMesh(
	string const& _tag, string const& _vertex_shader_tag, D3D11_PRIMITIVE_TOPOLOGY _topology,
	void* _vtx_data, int _vtx_size, int _vtx_count, D3D11_USAGE _vtx_usage)
{
	if (FindMesh(_tag))
		throw exception{ "ResourceManager::_CreateMesh" };

	auto mesh_buffer = shared_ptr<Mesh>{ new Mesh, [](Mesh* _p) {
		_p->_Release();
		delete _p;
	} };

	mesh_buffer->_CreateMesh(
		_tag, _vertex_shader_tag, _topology,
		_vtx_data, _vtx_size, _vtx_count, _vtx_usage
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

void ResourceManager::_LoadAnimation2DClip(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag)
{
	path path_buffer = PathManager::singleton()->FindPath(_path_tag);

	if (path_buffer.empty())
		throw std::exception{ "ResourceManager::_LoadAnimation2DClip" };

	std::wstring full_path = path_buffer.wstring() + _file_name;

	std::ifstream file{ full_path };

	if (file.fail())
		throw std::exception{ "ResourceManager::_LoadAnimation2DClip" };

	std::string line{};
	std::stringstream sstream{};

	getline(file, line); // skip attribute desc.
	getline(file, line);
	sstream.str(line);

	std::string type{};
	std::string option{};
	std::string animation_tag{};
	std::string texture_tag{};
	std::string width{};
	std::string height{};
	std::string completion_time{};

	getline(sstream, type, ',');
	getline(sstream, option, ',');
	getline(sstream, animation_tag, ',');
	getline(sstream, texture_tag, ',');
	getline(sstream, width, ',');
	getline(sstream, height, ',');
	getline(sstream, completion_time, ',');

	auto animation_2d_clip_desc = std::shared_ptr<Animation2DClipDesc>{ new Animation2DClipDesc, [](Animation2DClipDesc* _p) {
		delete _p;
	} };
	animation_2d_clip_desc->type = static_cast<ANIMATION_2D_TYPE>(stoi(type));
	animation_2d_clip_desc->option = static_cast<ANIMATION_OPTION>(stoi(option));
	animation_2d_clip_desc->texture_tag = texture_tag;

	if(!ResourceManager::singleton()->FindTexture(texture_tag))
		throw std::exception{ "ResourceManager::_LoadAnimation2DClip" };

	animation_2d_clip_desc->width = stof(width);
	animation_2d_clip_desc->height = stof(height);

	while (true)
	{
		std::string left{};
		std::string top{};
		std::string right{};
		std::string bottom{};

		std::string line_2{};
		std::stringstream sstream_2{};

		getline(file, line_2); // skip attribute desc.
		getline(file, line_2);
		sstream_2.str(line_2);

		if (line_2.empty())
			break;

		getline(sstream_2, left, ',');
		getline(sstream_2, top, ',');
		getline(sstream_2, right, ',');
		getline(sstream_2, bottom, ',');

		Animation2DFrameDesc animation_2d_frame_desc{};
		animation_2d_frame_desc.LT = Math::Vector2{ stof(left), stof(top) };
		animation_2d_frame_desc.RB = Math::Vector2{ stof(right), stof(bottom) };

		animation_2d_clip_desc->frame_vector.push_back(std::move(animation_2d_frame_desc));
	}

	animation_2d_clip_desc->completion_time = stof(completion_time);

	animation_2d_clip_map_.insert(make_pair(_tag, std::move(animation_2d_clip_desc)));
}
