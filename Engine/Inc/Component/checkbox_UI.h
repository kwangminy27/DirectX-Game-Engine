#pragma once

#include "button_UI.h"

namespace DG
{
	class DG_ENGINE_DLL CheckboxUI : public ButtonUI
	{
		friend class Object;
	public:
		virtual void Initialize() override;
		virtual void UpdateConstantBuffer();

		CHECKBOX_STATE checkbox_state() const;
		void set_checkbox_state(CHECKBOX_STATE _state);

	protected:
		CheckboxUI() = default;
		CheckboxUI(CheckboxUI const& _other);
		CheckboxUI(CheckboxUI&& _other) noexcept;
		CheckboxUI& operator=(CheckboxUI const&) = default;
		CheckboxUI& operator=(CheckboxUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		CHECKBOX_STATE checkbox_state_{};
	};
}
