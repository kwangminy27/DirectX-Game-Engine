#pragma once

#include "button_UI.h"

namespace DG
{
	class DG_ENGINE_DLL TitleBarUI : public ButtonUI
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		std::shared_ptr<Object> owner() const;
		bool click_flag() const;

		void set_owner(std::shared_ptr<Object> const& _owner);
		void set_click_flag(bool _flag);

	protected:
		TitleBarUI() = default;
		TitleBarUI(TitleBarUI const& _other);
		TitleBarUI(TitleBarUI&& _other) noexcept;
		TitleBarUI& operator=(TitleBarUI const&) = default;
		TitleBarUI& operator=(TitleBarUI&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
		virtual void _AfterClone();

		std::weak_ptr<Object> owner_{};
		bool click_flag_{};
	};
}
