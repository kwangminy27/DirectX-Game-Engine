#pragma once

#include "singleton.h"

namespace DG
{
	class Shader;

	class DG_ENGINE_DLL RenderingManager final : public Singleton<RenderingManager>
	{
		friend class Singleton<RenderingManager>;
	public:
		void Initialize();
		void UpdateConstantBuffer(std::string const& _tag, void* _data);
		std::shared_ptr<Shader> FindShader(std::string const& _tag);

	private:
		RenderingManager() = default;
		RenderingManager(RenderingManager const&) = delete;
		RenderingManager(RenderingManager&&) noexcept = delete;
		RenderingManager& operator=(RenderingManager const&) = delete;
		RenderingManager& operator=(RenderingManager&&) noexcept = delete;

		virtual void _Release() override;
	};
}
