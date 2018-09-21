#include "DGEngine_stdafx.h"
#include "shader_manager.h"

#include "device.h"
#include "shader.h"

using namespace std;
using namespace DG;

using Microsoft::WRL::ComPtr;

void ShaderManager::Initialize()
{
	try
	{
		vector<pair<SHADER_TYPE, wstring>> cso_info_vector{
			make_pair(SHADER_TYPE::VERTEX, L"BasicVS.cso"),
			make_pair(SHADER_TYPE::PIXEL, L"BasicPS.cso")
		};

		vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc_vector{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		_LoadCompiledShader(
			"BasicShader",
			cso_info_vector,
			input_element_desc_vector,
			"ShaderPath"
		);
	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
	catch (...)
	{
		cerr << "ShaderManager::Initialize" << endl;
	}
}

shared_ptr<Shader> const& ShaderManager::FindShader(string const& _tag) const
{
	auto iter = shader_map_.find(_tag);

	if (iter == shader_map_.end())
		return shader_nullptr_;

	return iter->second;
}

void ShaderManager::_Release()
{
}

void ShaderManager::_LoadCompiledShader(
	string const& _tag,
	vector<pair<SHADER_TYPE, wstring>> const& _cso_info_vector,
	vector<D3D11_INPUT_ELEMENT_DESC> const& input_element_desc_vector,
	string const& _path_tag)
{
	if (FindShader(_tag))
		throw exception{ "ShaderManager::_LoadCompiledShader" };

	auto shader_buffer = shared_ptr<Shader>{ new Shader, [](Shader* _p) {
		_p->_Release();
		delete _p;
	} };

	shader_buffer->_LoadCompiledShader(
		_tag,
		_cso_info_vector,
		input_element_desc_vector,
		_path_tag
	);

	shader_map_.insert(make_pair(_tag, move(shader_buffer)));
}
