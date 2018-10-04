#include "DGEngine_stdafx.h"
#include "texture.h"

#include "device.h"
#include "path_manager.h"

using namespace DG;

using std::filesystem::path;

Texture::Texture(Texture const& _other) : Tag(_other)
{
	texture_2d_vector_ = _other.texture_2d_vector_;
	SRV_ = _other.SRV_;
}

Texture::Texture(Texture&& _other) noexcept : Tag(std::move(_other))
{
	texture_2d_vector_ = std::move(_other.texture_2d_vector_);
	SRV_ = std::move(_other.SRV_);
}

void Texture::_Release()
{
}

void Texture::_LoadTexture2D(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag)
{
	path path_buffer = PathManager::singleton()->FindPath(_path_tag);

	if (path_buffer.empty())
		throw std::exception{ "Texture::_LoadTexture2D" };

	tag_ = _tag;

	path_buffer /= _file_name;

	path extension = path_buffer.extension();

	auto const& device = Device::singleton()->device();

	Microsoft::WRL::ComPtr<ID3D11Resource> resource{};
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_2d{};

	if (extension.string() == ".dds")
		ThrowIfFailed(DirectX::CreateDDSTextureFromFile(device.Get(), _file_name.c_str(), &resource, &SRV_));
	else
		ThrowIfFailed(DirectX::CreateWICTextureFromFile(device.Get(), _file_name.c_str(), &resource, &SRV_));

	ThrowIfFailed(resource.As(&texture_2d));

	texture_2d_vector_.push_back(std::move(texture_2d));
}

void Texture::_SetShaderResourceView(int _slot)
{
	Device::singleton()->context()->PSSetShaderResources(_slot, 1, SRV_.GetAddressOf());
}
