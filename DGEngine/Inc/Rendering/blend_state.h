#pragma once

#include "render_state.h"

namespace DG
{
	class DG_ENGINE_DLL BlendState final : public RenderState
	{
		friend class RenderingManager;
	public:
		virtual void Initialize() override;

	protected:
		BlendState() = default;
		BlendState(BlendState const& _other);
		BlendState(BlendState&& _other) noexcept;
		BlendState& operator=(BlendState const&) = default;
		BlendState& operator=(BlendState&&) noexcept = default;

		virtual void _Release() override;

		virtual void _SetState() override;
		virtual void _SetBackState() override;

		void _AddRenderTargetBlendDesc(
			bool _blend_enable,
			D3D11_BLEND _src_blend = D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND _dest_blend = D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP _blend_op = D3D11_BLEND_OP_ADD,
			D3D11_BLEND _src_blend_alpha = D3D11_BLEND_ONE,
			D3D11_BLEND _dest_blend_alpha = D3D11_BLEND_ZERO,
			D3D11_BLEND_OP _blend_op_alpha = D3D11_BLEND_OP_ADD,
			UINT8 render_target_write_mask = D3D11_COLOR_WRITE_ENABLE_ALL);
		void _CreateBlendState(bool _alpha_to_coverage_enable, bool _independent_blend_enable);

		std::vector<D3D11_RENDER_TARGET_BLEND_DESC> render_target_blend_desc_vector_buffer_{};
	};
}
