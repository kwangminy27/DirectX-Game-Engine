#pragma once

#include "tag.h"

namespace DG
{
	class DG_ENGINE_DLL RenderState : public Tag
	{
		friend class RenderingManager;
	protected:
		RenderState() = default;
		RenderState(RenderState const& _other);
		RenderState(RenderState&& _other) noexcept;
		RenderState& operator=(RenderState const&) = default;
		RenderState& operator=(RenderState&&) noexcept = default;
		virtual ~RenderState() = default;

		virtual void _Release() override;

		Microsoft::WRL::ComPtr<ID3D11DeviceChild> state_{};
	};
}
