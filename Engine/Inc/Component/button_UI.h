#pragma once

#include "UI.h"

namespace DG
{
	class Collider;

	// 나중에 이름을 ClickUI로 변경하자.
	class DG_ENGINE_DLL ButtonUI : public UI
	{
		friend class Object;
	public:
		virtual void Initialize() override;
		virtual void UpdateConstantBuffer();

		void Enable();
		void Disable();

		BUTTON_STATE button_state() const;

		void set_button_state(BUTTON_STATE _state);
		void set_callback(std::function<void(float)> const& _function);

	protected:
		ButtonUI() = default;
		ButtonUI(ButtonUI const& _other);
		ButtonUI(ButtonUI&& _other) noexcept;
		ButtonUI& operator=(ButtonUI const&) = default;
		ButtonUI& operator=(ButtonUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		void _MouseOn(Collider* _src, Collider* _dest, float _time);
		void _MouseOff(Collider* _src, Collider* _dest, float _time);

		BUTTON_STATE button_state_{};
		std::function<void(float)> callback_{};
		std::array<Math::Vector4, static_cast<int>(BUTTON_STATE::END)> color_array_{};
	};
}
