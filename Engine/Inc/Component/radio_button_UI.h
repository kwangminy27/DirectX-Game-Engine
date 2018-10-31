#pragma once

#include "checkbox_UI.h"

namespace DG
{
	class DG_ENGINE_DLL RadioButtonUI : public CheckboxUI
	{
		friend class Object;
	public:
		virtual void Initialize() override;
		virtual void UpdateConstantBuffer();

		int group() const;
		void set_group(int _group);

	protected:
		RadioButtonUI() = default;
		RadioButtonUI(RadioButtonUI const& _other);
		RadioButtonUI(RadioButtonUI&& _other) noexcept;
		RadioButtonUI& operator=(RadioButtonUI const&) = default;
		RadioButtonUI& operator=(RadioButtonUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		int group_{};
	};
}

