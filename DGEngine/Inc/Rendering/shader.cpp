#include "DGEngine_stdafx.h"
#include "shader.h"

#include "device.h"
#include "path_manager.h"

using namespace std;
using namespace filesystem;
using namespace DG;

using Microsoft::WRL::ComPtr;

void Shader::SetShader()
{
	auto const& context = Device::singleton()->context();

	context->IASetInputLayout(input_layout_.Get());
	context->VSSetShader(VS_.Get(), nullptr, 0);
	context->PSSetShader(PS_.Get(), nullptr, 0);
}

Shader::Shader(Shader const& _other) : Tag(_other)
{
	input_layout_ = _other.input_layout_;
	VS_ = _other.VS_;
	PS_ = _other.PS_;
}

Shader::Shader(Shader&& _other) noexcept : Tag(move(_other))
{
	input_layout_ = move(_other.input_layout_);
	VS_ = move(_other.VS_);
	PS_ = move(_other.PS_);
}

void Shader::_Release()
{
}

void Shader::_LoadCompiledShader(
	string const& _tag,
	vector<pair<SHADER_TYPE, wstring>> const& _cso_info_vector,
	vector<D3D11_INPUT_ELEMENT_DESC> const& input_element_desc_vector, 
	string const& _path_tag)
{
	tag_ = _tag;

	for (auto& cso_info : _cso_info_vector)
	{
		switch (cso_info.first)
		{
		case SHADER_TYPE::VERTEX:
			_LoadCompiledVertexShader(cso_info.second, input_element_desc_vector, _path_tag);
			break;
		case SHADER_TYPE::PIXEL:
			_LoadCompiledPixelShader(cso_info.second, _path_tag);
			break;
		}
	}
}

void Shader::_LoadCompiledVertexShader(
	wstring const& _file_name,
	vector<D3D11_INPUT_ELEMENT_DESC> const& input_element_desc_vector,
	string const& _path_tag)
{
	path path_buffer = PathManager::singleton()->FindPath(_path_tag);

	if (path_buffer.empty())
		throw exception{ "Shader::_LoadCompiledVertexShader" };

	wstring full_path = path_buffer.wstring() + _file_name;

	ifstream cso{ full_path, ios::ate | ios::binary };

	int size = static_cast<int>(cso.tellg());

	cso.seekg(0, ios::beg);

	auto buffer = unique_ptr<BYTE[], function<void(BYTE*)>>{ new BYTE[size], [](BYTE* _p) {
		delete[] _p;
	} };

	cso.read(reinterpret_cast<char*>(buffer.get()), size);

	auto const& Device = Device::singleton();

	ThrowIfFailed(
		Device->device()->CreateInputLayout(
			input_element_desc_vector.data(),
			static_cast<UINT>(input_element_desc_vector.size()),
			reinterpret_cast<void*>(buffer.get()),
			static_cast<SIZE_T>(size),
			&input_layout_
		)
	);

	ThrowIfFailed(
		Device->device()->CreateVertexShader(
			buffer.get(),
			size,
			nullptr,
			&VS_
		)
	);
}

void Shader::_LoadCompiledPixelShader(wstring const& _file_name, string const& _path_tag)
{
	path path_buffer = PathManager::singleton()->FindPath(_path_tag);

	if (path_buffer.empty())
		throw exception{ "Shader::_LoadCompiledPixelShader" };

	wstring full_path = path_buffer.wstring() + _file_name;

	ifstream cso{ full_path, ios::ate | ios::binary };

	int size = static_cast<int>(cso.tellg());

	cso.seekg(0, ios::beg);

	auto buffer = unique_ptr<BYTE[], function<void(BYTE*)>>{ new BYTE[size], [](BYTE* _p) {
		delete[] _p;
	} };

	cso.read(reinterpret_cast<char*>(buffer.get()), size);

	ThrowIfFailed(
		Device::singleton()->device()->CreatePixelShader(
			buffer.get(),
			size,
			nullptr,
			&PS_
		)
	);
}
