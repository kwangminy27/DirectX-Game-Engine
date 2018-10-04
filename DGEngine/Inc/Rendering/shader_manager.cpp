#include "DGEngine_stdafx.h"
#include "shader_manager.h"

#include "device.h"
#include "shader.h"

using namespace DG;

using Microsoft::WRL::ComPtr;

std::shared_ptr<Shader> ShaderManager::shader_nullptr_{};
std::shared_ptr<ConstantBuffer> ShaderManager::constant_buffer_nullptr_{};

void ShaderManager::Initialize()
{
	try
	{
		// BasicShader
		vector<pair<SHADER_TYPE, wstring>> cso_info_vector{};
		vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc_vector{};

		cso_info_vector.push_back(make_pair(SHADER_TYPE::VERTEX, L"BasicVS.cso"));
		cso_info_vector.push_back(make_pair(SHADER_TYPE::PIXEL, L"BasicPS.cso"));

		input_element_desc_vector.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		input_element_desc_vector.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		_LoadCompiledShader(
			"BasicShader",
			cso_info_vector,
			input_element_desc_vector,
			"ShaderPath"
		);

		// BasicTexShader
		cso_info_vector.clear();
		input_element_desc_vector.clear();

		cso_info_vector.push_back(make_pair(SHADER_TYPE::VERTEX, L"BasicTexVS.cso"));
		cso_info_vector.push_back(make_pair(SHADER_TYPE::PIXEL, L"BasicTexPS.cso"));

		input_element_desc_vector.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		input_element_desc_vector.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		_LoadCompiledShader(
			"BasicTexShader",
			cso_info_vector,
			input_element_desc_vector,
			"ShaderPath"
		);

		_CreateConstantBuffer(
			"Transform",
			sizeof(TransformConstantBuffer),
			static_cast<int>(CONSTANT_BUFFER_SHADER_TYPE::VERTEX) | static_cast<int>(CONSTANT_BUFFER_SHADER_TYPE::PIXEL)
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

std::shared_ptr<ConstantBuffer> const& ShaderManager::FindConstantBuffer(std::string const& _tag) const
{
	auto iter = constant_buffer_map_.find(_tag);

	if (iter == constant_buffer_map_.end())
		return constant_buffer_nullptr_;

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

void ShaderManager::_CreateConstantBuffer(std::string const& _tag, int _size, int _shader_type)
{
	if (FindConstantBuffer(_tag))
		throw std::exception{ "ShaderManager::_CreateConstantBuffer" };

	auto constant_buffer = std::shared_ptr<ConstantBuffer>{ new ConstantBuffer, [](ConstantBuffer* _p) {
		delete _p;
	} };
	constant_buffer->size = _size;
	constant_buffer->shader_type = _shader_type;

	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.ByteWidth = _size;
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ThrowIfFailed(Device::singleton()->device()->CreateBuffer(&buffer_desc, nullptr, &constant_buffer->buffer));

	constant_buffer_map_.insert(make_pair(_tag, std::move(constant_buffer)));
}

void ShaderManager::_UpdateConstantBuffer(std::string const& _tag, void* _data)
{
	auto const& constant_buffer = FindConstantBuffer(_tag);

	if (!constant_buffer)
		throw std::exception{ "ShaderManager::_UpdateConstantBuffer" };

	auto const& context = Device::singleton()->context();

	D3D11_MAPPED_SUBRESOURCE mapped_subresource{};
	ThrowIfFailed(context->Map(constant_buffer->buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource));
	memcpy_s(mapped_subresource.pData, constant_buffer->size, _data, constant_buffer->size);
	context->Unmap(constant_buffer->buffer.Get(), 0);

	if (constant_buffer->shader_type & static_cast<int>(CONSTANT_BUFFER_SHADER_TYPE::VERTEX))
		context->VSSetConstantBuffers(0, 1, constant_buffer->buffer.GetAddressOf());

	if (constant_buffer->shader_type & static_cast<int>(CONSTANT_BUFFER_SHADER_TYPE::PIXEL))
		context->PSSetConstantBuffers(0, 1, constant_buffer->buffer.GetAddressOf());
}
