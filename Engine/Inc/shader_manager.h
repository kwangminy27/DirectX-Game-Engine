#pragma once

#include "singleton.h"

namespace DG
{
	class Shader;

	class ShaderManager final : public Singleton<ShaderManager>
	{
		friend class Singleton<ShaderManager>;
	public:
		void Initialize();
		std::shared_ptr<Shader> const& FindShader(std::string const& _tag);
		Microsoft::WRL::ComPtr<ID3D11InputLayout> const& FindInputLayout(std::string const& _tag);

	private:
		ShaderManager() = default;
		ShaderManager(ShaderManager const&) = delete;
		ShaderManager(ShaderManager&&) noexcept = delete;
		ShaderManager& operator=(ShaderManager const&) = delete;
		ShaderManager& operator=(ShaderManager&&) noexcept = delete;

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
		void _CreateInputLayout(std::string const& _tag, std::string const& _shader_tag);
		void _AddInputElementDesc(
			std::string const& _semantic_tag, UINT _semantic_idx, DXGI_FORMAT _format, UINT _input_slot, UINT _aligned_byte_offset,
			D3D11_INPUT_CLASSIFICATION _input_slot_class, UINT _instance_data_step_rate);

		std::shared_ptr<Shader> shader_nullptr_{};
		std::unordered_map<std::string, std::shared_ptr<Shader>> shader_map_{};
		Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_nullptr_{};
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11InputLayout>> input_layout_map_{};
		std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc_vector_{};
	};
}
