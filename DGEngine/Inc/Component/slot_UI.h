#pragma once

#include "button_UI.h"

namespace DG
{
	class DG_ENGINE_DLL SlotUI final : public UI
	{
		friend class Object;
	public:
		virtual void Initialize() override;

	protected:
		SlotUI() = default;
		SlotUI(SlotUI const& _other);
		SlotUI(SlotUI&& _other) noexcept;
		SlotUI& operator=(SlotUI const&) = default;
		SlotUI& operator=(SlotUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();
	};
}
