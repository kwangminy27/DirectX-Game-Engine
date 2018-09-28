#pragma once

#include "tag.h"

namespace DG
{
	class DG_ENGINE_DLL Shader : public Tag
	{
		friend class ShaderManager;
	public:
		void SetShader();

	protected:
		Shader() = default;
		Shader(Shader const& _other);
		Shader(Shader&& _other) noexcept;
		Shader& operator=(Shader const&) = default;
		Shader& operator=(Shader&&) noexcept = default;

		virtual void _Release() override;

		void _LoadCompiledShader(
			std::string const& _tag,
			std::vector<std::pair<SHADER_TYPE, std::wstring>> const& _cso_info_vector,
			std::vector<D3D11_INPUT_ELEMENT_DESC> const& input_element_desc_vector,
			std::string const& _path_tag);
		void _LoadCompiledVertexShader(
			std::wstring const& _file_name,
			std::vector<D3D11_INPUT_ELEMENT_DESC> const& input_element_desc_vector,
			std::string const& _path_tag);
		void _LoadCompiledPixelShader(std::wstring const& _file_name, std::string const& _path_tag);

		Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_{};
		Microsoft::WRL::ComPtr<ID3D11VertexShader> VS_{};
		Microsoft::WRL::ComPtr<ID3D11PixelShader> PS_{};
	};
}
