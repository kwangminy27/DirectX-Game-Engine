#pragma once

#include "render_state.h"

namespace DG
{
	class DG_ENGINE_DLL BlendState final : public RenderState
	{
		friend class RenderingManager;
	protected:
		BlendState() = default;
		BlendState(BlendState const& _other);
		BlendState(BlendState&& _other) noexcept;
		BlendState& operator=(BlendState const&) = default;
		BlendState& operator=(BlendState&&) noexcept = default;

		virtual void _Release() override;
	};
}
