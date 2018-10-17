#pragma once

#include "render_state.h"

namespace DG
{
	class DG_ENGINE_DLL DepthStencilState final : public RenderState
	{
		friend class RenderingManager;
	public:
		virtual void Initialize() override;

	protected:
		DepthStencilState() = default;
		DepthStencilState(DepthStencilState const& _other);
		DepthStencilState(DepthStencilState&& _other) noexcept;
		DepthStencilState& operator=(DepthStencilState const&) = default;
		DepthStencilState& operator=(DepthStencilState&&) noexcept = default;

		virtual void _Release() override;

		virtual void _SetState() override;
		virtual void _SetBackState() override;

		void _CreateState(
			BOOL _depth_enable,
			D3D11_DEPTH_WRITE_MASK _depth_write_mask,
			D3D11_COMPARISON_FUNC _depth_func,
			BOOL _stencil_enable,
			UINT8 _stencil_read_mask,
			UINT8 _stencil_write_mask,
			D3D11_DEPTH_STENCILOP_DESC const& _front_face,
			D3D11_DEPTH_STENCILOP_DESC const& _back_face);

		UINT stencil_ref_{};
		UINT old_stencil_ref_{};
	};
}
