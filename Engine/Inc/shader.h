#pragma once

#include "tag.h"

namespace DG
{
	class Shader : public Tag
	{
		friend class ShaderManager;
	public:
		void SetShader();

		void* GetVSCode() const;
		SIZE_T GetVSCodeSize() const;

		void* VS_cso_buffer() const;
		int VS_cso_size() const;

	protected:
		Shader() = default;
		Shader(Shader const& _other);
		Shader(Shader&& _other) noexcept;
		Shader& operator=(Shader const&) = default;
		Shader& operator=(Shader&&) noexcept = default;

		virtual void _Release() override;

		void _LoadShader(
			std::string const& _tag,
			std::wstring const& _file_name,
			std::array<std::string, static_cast<int>(SHADER_TYPE::END)> const& _entry_array,
			std::string const& _path_tag);
		void _LoadCompiledShader(
			std::string const& _tag,
			std::vector<std::wstring> const& _file_name_vector,
			std::string const& _path_tag);
		void _LoadVertexShader(std::wstring const& _file_name, std::string const& _entry, std::string const& _path_tag);
		void _LoadPixelShader(std::wstring const& _file_name, std::string const& _entry, std::string const& _path_tag);
		void _LoadCompiledVertexShader(std::wstring const& _file_name, std::string const& _path_tag);
		void _LoadCompiledPixelShader(std::wstring const& _file_name, std::string const& _path_tag);

		Microsoft::WRL::ComPtr<ID3D11VertexShader> VS_{};
		Microsoft::WRL::ComPtr<ID3D11PixelShader> PS_{};
		Microsoft::WRL::ComPtr<ID3DBlob> VS_blob_{};
		Microsoft::WRL::ComPtr<ID3DBlob> PS_blob_{};
		std::unique_ptr<BYTE[], std::function<void(BYTE*)>> VS_cso_buffer_{};
		std::unique_ptr<BYTE[], std::function<void(BYTE*)>> PS_cso_buffer_{};
		std::streamoff VS_cso_size_{};
		std::streamoff PS_cso_size_{};
	};
}
