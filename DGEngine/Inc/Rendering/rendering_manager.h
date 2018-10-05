#pragma once

#include "singleton.h"

namespace DG
{
	class Shader;
	class RenderState;

	class DG_ENGINE_DLL RenderingManager final : public Singleton<RenderingManager>
	{
		friend class Singleton<RenderingManager>;
	public:
		void Initialize();

		void AddRenderTargetBlendDesc(
			bool _blend_enable,
			D3D11_BLEND _src_blend = D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND _dest_blend = D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP _blend_op = D3D11_BLEND_OP_ADD,
			D3D11_BLEND _src_blend_alpha = D3D11_BLEND_ONE,
			D3D11_BLEND _dest_blend_alpha = D3D11_BLEND_ZERO,
			D3D11_BLEND_OP _blend_op_alpha = D3D11_BLEND_OP_ADD,
			UINT8 render_target_write_mask = D3D11_COLOR_WRITE_ENABLE_ALL);
		void CreateBlendState(std::string const& _tag, bool _alpha_to_coverage_enable, bool _independent_blend_enable);

		std::shared_ptr<Shader> const& FindShader(std::string const& _tag) const;
		std::shared_ptr<RenderState> const& FindRenderState(std::string const& _tag) const;

		void UpdateConstantBuffer(std::string const& _tag, void* _data);

	private:
		RenderingManager() = default;
		RenderingManager(RenderingManager const&) = delete;
		RenderingManager(RenderingManager&&) noexcept = delete;
		RenderingManager& operator=(RenderingManager const&) = delete;
		RenderingManager& operator=(RenderingManager&&) noexcept = delete;

		virtual void _Release() override;

		static std::shared_ptr<RenderState> render_state_nullptr_;
		std::unordered_map<std::string, std::shared_ptr<RenderState>> render_state_map_{};
	};
}
