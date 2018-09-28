#pragma once

#include "singleton.h"

namespace DG
{
	class Shader;

	class DG_ENGINE_DLL ShaderManager final : public Singleton<ShaderManager>
	{
		friend class Singleton<ShaderManager>;
	public:
		void Initialize();
		std::shared_ptr<Shader> const& FindShader(std::string const& _tag) const;

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

		std::shared_ptr<Shader> shader_nullptr_{};
		std::unordered_map<std::string, std::shared_ptr<Shader>> shader_map_{};
	};
}
