#pragma once

#include "singleton.h"

namespace DG
{
	class Shader;

	class DG_ENGINE_DLL ShaderManager final : public Singleton<ShaderManager>
	{
		friend class Singleton<ShaderManager>;
		friend class RenderingManager;
	public:
		void Initialize();
		std::shared_ptr<Shader> const& FindShader(std::string const& _tag) const;
		std::shared_ptr<ConstantBuffer> const& FindConstantBuffer(std::string const& _tag) const;

	private:
		ShaderManager() = default;
		ShaderManager(ShaderManager const&) = delete;
		ShaderManager(ShaderManager&&) noexcept = delete;
		ShaderManager& operator=(ShaderManager const&) = delete;
		ShaderManager& operator=(ShaderManager&&) noexcept = delete;

		virtual void _Release() override;

		void _LoadCompiledShader(
			std::string const& _tag,
			std::vector<std::pair<SHADER_TYPE, std::wstring>> const& _cso_info_vector,
			std::vector<D3D11_INPUT_ELEMENT_DESC> const& input_element_desc_vector,
			std::string const& _path_tag);
		void _CreateConstantBuffer(std::string const& _tag, int _size, int _shader_type, int _slot);
		void _UpdateConstantBuffer(std::string const& _tag, void* _data);

		static std::shared_ptr<Shader> shader_nullptr_;
		static std::shared_ptr<ConstantBuffer> constant_buffer_nullptr_;
		std::unordered_map<std::string, std::shared_ptr<Shader>> shader_map_{};
		std::unordered_map<std::string, std::shared_ptr<ConstantBuffer>> constant_buffer_map_{};
	};
}
