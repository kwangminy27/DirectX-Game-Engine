#pragma once

#include "tag.h"

namespace DG
{
	class DG_ENGINE_DLL RenderState : public Tag
	{
		friend class RenderingManager;
		friend class Renderer;
		friend class Stage;
	public:
		virtual void Initialize() = 0;

		Microsoft::WRL::ComPtr<ID3D11DeviceChild> state() const;
		RENDER_STATE_TYPE type() const;

	protected:
		RenderState() = default;
		RenderState(RenderState const& _other);
		RenderState(RenderState&& _other) noexcept;
		RenderState& operator=(RenderState const&) = default;
		RenderState& operator=(RenderState&&) noexcept = default;
		virtual ~RenderState() = default;

		virtual void _Release() override;

		virtual void _SetState() = 0;
		virtual void _SetBackState() = 0;

		Microsoft::WRL::ComPtr<ID3D11DeviceChild> state_{};
		Microsoft::WRL::ComPtr<ID3D11DeviceChild> old_state_{};
		RENDER_STATE_TYPE type_{};
	};
}
